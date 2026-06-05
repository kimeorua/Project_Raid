// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/PR_GameIntance.h"

#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "UI/PR_LobbyMenu_Sub.h"
#include "UI/PR_MainMenu_Top.h"
#include "PlayerController/PR_MainMenuController.h"

void UPR_GameIntance::Login()
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

void UPR_GameIntance::Init()
{
	Super::Init();
	
	OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IdentityPtr = OnlineSubsystem->GetIdentityInterface();
		
		if (IdentityPtr.IsValid())
		{
			LoginDelegateHandle = IdentityPtr->OnLoginCompleteDelegates->AddUObject(this, &UPR_GameIntance::LoginComleted);
		}
	}
	SessionPtr = OnlineSubsystem->GetSessionInterface();
	SessionPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UPR_GameIntance::OnCreateSessionCompleted);
}

void UPR_GameIntance::Shutdown()
{
	if (IdentityPtr.IsValid() && LoginDelegateHandle.IsValid())
	{
		IdentityPtr->OnLoginCompleteDelegates->Remove(LoginDelegateHandle);
	}
	
	IdentityPtr = nullptr;
	SessionPtr = nullptr;
	OnlineSubsystem = nullptr;

	Super::Shutdown();
}

void UPR_GameIntance::CreateSession(const FString& RoomName)
{
	if (!SessionPtr) { return; }
	
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
	
	SessionPtr->CreateSession(0, NAME_GameSession, OnlineSessionSettings);
}

void UPR_GameIntance::OnCreateSessionCompleted(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (APR_MainMenuController* PC = Cast<APR_MainMenuController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
		{
			if (UPR_MainMenu_Top* MasterUI = PC->GetMasterUI())
			{
				if (UPR_LobbyMenu_Sub* LobbySub = MasterUI->GetLobbySubWidget())
				{
					if (FNamedOnlineSession* ActiveSession = SessionPtr->GetNamedSession(SessionName))
					{
						LobbySub->AddMyCreatedSessionToList(ActiveSession->SessionSettings);
					}
				}
			}
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

void UPR_GameIntance::LoginComleted(int NumOfPlayer, bool bSuccessful, const FUniqueNetId& UserID, const FString& Error)
{
	if (bSuccessful)
	{
		if (APR_MainMenuController* PR_PC = Cast<APR_MainMenuController>(UGameplayStatics::GetPlayerController(GetWorld(), NumOfPlayer)))
		{
			PR_PC->ShowLobbyUI();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Login failed %s"), *Error);
	}
}
