// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/PR_GameIntance.h"

#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"

#include "Kismet/GameplayStatics.h"

void UPR_GameIntance::Login()
{
	FOnlineAccountCredentials OnlineAccountCredentials;
#if WITH_EDITOR
	if (GetWorld() && GetWorld()->IsPlayInEditor())
	{
		UE_LOG(LogTemp, Warning, TEXT("[PIE] 에디터 플레이 구동: 기본 HostUser로 로그인"));
       
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
}

void UPR_GameIntance::Shutdown()
{
	if (IdentityPtr.IsValid() && LoginDelegateHandle.IsValid())
	{
		IdentityPtr->OnLoginCompleteDelegates->Remove(LoginDelegateHandle);
	}

	Super::Shutdown();
}

void UPR_GameIntance::LoginComleted(int NumOfPlayer, bool bSuccessful, const FUniqueNetId& UserID, const FString& Error)
{
	if (bSuccessful)
	{
		MoveToLobby();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Login failed %s"), *Error);
	}
}

void UPR_GameIntance::MoveToLobby() const
{
	if (!LobbyLevelRef.IsValid())
	{
		LobbyLevelRef.LoadSynchronous();
	}
	if (LobbyLevelRef.IsValid() && GetWorld())
	{
		const FName LevelName = FName(*FPackageName::ObjectPathToPackageName(LobbyLevelRef.ToString()));
		UGameplayStatics::OpenLevel(GetWorld(), LevelName);
	}
}
