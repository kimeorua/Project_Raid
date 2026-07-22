// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/PR_GameInstance.h"

#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"

#include "UI/PR_LobbyMenu_Sub.h"
#include "UI/PR_MainMenu_Top.h"
#include "PlayerController/PR_MainMenuController.h"
#include "UI/PR_MainMenu_Sub.h"

void UPR_GameInstance::Login()
{
	FOnlineAccountCredentials OnlineAccountCredentials;
#if WITH_EDITOR
	if (GetWorld() && GetWorld()->IsPlayInEditor())
	{
		OnlineAccountCredentials.Type = TEXT("developer");
		OnlineAccountCredentials.Id = TEXT("127.0.0.1:8081");
		OnlineAccountCredentials.Token = TEXT("HostUser");
	}
	// 2. bat 파일 실행
	else
	{
		OnlineAccountCredentials.Type = TEXT("developer");
		OnlineAccountCredentials.Id = TEXT("127.0.0.1:8081");
		
		FString ParsedToken;
		if (FParse::Value(FCommandLine::Get(), TEXT("AUTH_CREDENTIALS="), ParsedToken))
		{
			OnlineAccountCredentials.Token = ParsedToken; 
			UE_LOG(LogTemp, Log, TEXT("[BAT RUN] Command line token found: %s"), *ParsedToken);
		}
		else
		{
			OnlineAccountCredentials.Token = TEXT("HostUser");
		}
	}
#else
	OnlineAccountCredentials.Type = TEXT("persistentauth");
	OnlineAccountCredentials.Id = TEXT("");
	OnlineAccountCredentials.Token = TEXT("");
#endif

	IdentityPtr->Login(0, OnlineAccountCredentials);
}

void UPR_GameInstance::Init()
{
	Super::Init();
	GEngine->OnNetworkFailure().AddUObject(this, &UPR_GameInstance::HandleNetworkFailure);
	
	OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IdentityPtr = OnlineSubsystem->GetIdentityInterface();
		
		if (IdentityPtr.IsValid())
		{
			LoginDelegateHandle = IdentityPtr->OnLoginCompleteDelegates->AddUObject(this, &UPR_GameInstance::LoginComleted);
		}
	}
	
	SessionPtr = OnlineSubsystem->GetSessionInterface();
	
	if (SessionPtr.IsValid())
	{
		FindSessionsDelegateHandle = SessionPtr->OnFindSessionsCompleteDelegates.AddUObject(this, &UPR_GameInstance::OnFindSessionsCompleted);
		SessionPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UPR_GameInstance::OnCreateSessionCompleted);
		SessionPtr->OnJoinSessionCompleteDelegates.AddUObject(this, &UPR_GameInstance::OnJoinSessionCompleted);
	}
}

void UPR_GameInstance::Shutdown()
{
	if (IdentityPtr.IsValid() && LoginDelegateHandle.IsValid())
	{
		IdentityPtr->OnLoginCompleteDelegates->Remove(LoginDelegateHandle);
	}
	if (SessionPtr.IsValid() && FindSessionsDelegateHandle.IsValid())
	{
		SessionPtr->OnFindSessionsCompleteDelegates.Remove(FindSessionsDelegateHandle);
	}
	
	OnlineSubsystem = nullptr;
	IdentityPtr = nullptr;
	SessionPtr = nullptr;
	
	Super::Shutdown();
}

void UPR_GameInstance::CreateSession(const FString& RoomName)
{
	if (!SessionPtr) {return;}
	
	FString FinalRoomName = RoomName.IsEmpty() ? TEXT("Default Raid Room") : RoomName;
	
	FOnlineSessionSettings OnlineSessionSettings;
	OnlineSessionSettings.bAllowInvites = true;
	OnlineSessionSettings.bIsDedicated = false;
	OnlineSessionSettings.bIsLANMatch = false;
	OnlineSessionSettings.bShouldAdvertise = true;
	OnlineSessionSettings.bUseLobbiesIfAvailable = true;
	OnlineSessionSettings.bUsesPresence = true;
	OnlineSessionSettings.bAllowJoinViaPresence = true;
	OnlineSessionSettings.NumPublicConnections = 4;
	
	OnlineSessionSettings.Set(FName("LobbyName"), RoomName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	OnlineSessionSettings.Set(FName("IsMatchStarted"), FString("False"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	SessionPtr->CreateSession(0, NAME_GameSession, OnlineSessionSettings);
}

void UPR_GameInstance::OnCreateSessionCompleted(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (!SelectLevel.IsValid())
		{
			SelectLevel.LoadSynchronous();
		}
		if (SelectLevel.IsValid())
		{
			const FName LevelName = *FPackageName::ObjectPathToPackageName(SelectLevel.ToString());
			GetWorld()->ServerTravel(LevelName.ToString() + "?listen");
		}
	}
	else
	{
		if (APR_MainMenuController* PC = Cast<APR_MainMenuController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
		{
			if (UPR_MainMenu_Top* MasterUI = PC->GetMasterUI())
			{
				if (UPR_LobbyMenu_Sub* LobbySub = MasterUI->GetLobbySubWidget())
				{
					LobbySub->ResetCreateButton();
				}
			}
		}
	}
}

void UPR_GameInstance::FindSessions()
{
	if (!SessionPtr.IsValid()) return;
	
	SessionSearchSettings = MakeShareable(new FOnlineSessionSearch());
	
	SessionSearchSettings->bIsLanQuery = false;
	SessionSearchSettings->MaxSearchResults = 20;
	
	SessionSearchSettings->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);
	SessionSearchSettings->QuerySettings.Set(FName("LobbyName"), FString(""), EOnlineComparisonOp::NotEquals);
	SessionSearchSettings->QuerySettings.Set(FName("IsMatchStarted"), FString("False"), EOnlineComparisonOp::Equals);
	
	SessionPtr->FindSessions(0, SessionSearchSettings.ToSharedRef());
}

void UPR_GameInstance::JoinSelectedSession(const FOnlineSessionSearchResult& TargetSession)
{
	if (!SessionPtr.IsValid()) { return; }
	SessionPtr->JoinSession(0, NAME_GameSession, TargetSession);
}

void UPR_GameInstance::HideSessionOnMatchStart()
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (!Subsystem) return;

	IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
	if (!SessionInterface.IsValid()) return;
    
	FOnlineSessionSettings* CurrentSettings = SessionInterface->GetSessionSettings(NAME_GameSession);
    
	if (CurrentSettings)
	{
		CurrentSettings->Set(FName("IsMatchStarted"), FString("True"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		SessionInterface->UpdateSession(NAME_GameSession, *CurrentSettings, true);
	}
}

void UPR_GameInstance::LoginComleted(int NumOfPlayer, bool bSuccessful, const FUniqueNetId& UserID, const FString& Error)
{
	if (bSuccessful)
	{
		if (APR_MainMenuController* PR_PC = Cast<APR_MainMenuController>(UGameplayStatics::GetPlayerController(GetWorld(), NumOfPlayer)))
		{
			PR_PC->GetMasterUI()->GetMainMenuSubWidget()->ResetButtons();
			PR_PC->ShowLobbyUI();
		}
	}
	else
	{
		if (APR_MainMenuController* PR_PC = Cast<APR_MainMenuController>(UGameplayStatics::GetPlayerController(GetWorld(), NumOfPlayer)))
		{
			PR_PC->GetMasterUI()->GetMainMenuSubWidget()->ResetButtons();
		}
		UE_LOG(LogTemp, Warning, TEXT("Login failed %s"), *Error);
	}
}

void UPR_GameInstance::OnFindSessionsCompleted(bool bWasSuccessful)
{
	if (APR_MainMenuController* PC = Cast<APR_MainMenuController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		if (UPR_MainMenu_Top* MasterUI = PC->GetMasterUI())
		{
			if (UPR_LobbyMenu_Sub* LobbySub = MasterUI->GetLobbySubWidget())
			{
				if (bWasSuccessful && SessionSearchSettings.IsValid())
				{
					LobbySub->UpdateSessionListView(SessionSearchSettings->SearchResults);
					LobbySub->ResetAllButtons();
				}
			}
		}
	}
}

void UPR_GameInstance::OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PC && SessionPtr.IsValid())
		{
			FString ConnectAddress;
			if (SessionPtr->GetResolvedConnectString(SessionName, ConnectAddress))
			{
				PC->ClientTravel(ConnectAddress, ETravelType::TRAVEL_Absolute);
			}
		}
	}
	else {return;}
}

void UPR_GameInstance::HandleNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	bShouldSkipLoginAndGoToLobby = true;
}
