// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "PR_GameIntance.generated.h"

class IOnlineSubsystem;

UCLASS()
class PROJECT_RAID_API UPR_GameIntance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
    void Login();
	
	virtual  void Init() override;
	virtual void Shutdown() override;
	
	UFUNCTION()
	void CreateSession(const FString& RoomName);
	
	UFUNCTION()
	void OnCreateSessionCompleted(FName SessionName, bool bWasSuccessful);
	
	void FindSessions();
	void JoinSelectedSession(const FOnlineSessionSearchResult& TargetSession);
	
	bool CheckSkipLogin() { return bShouldSkipLoginAndGoToLobby; }
	void ResetSkipLogin() { bShouldSkipLoginAndGoToLobby = false; }
	
private:
	IOnlineSubsystem* OnlineSubsystem;
	IOnlineIdentityPtr IdentityPtr;
	IOnlineSessionPtr SessionPtr;
	TSharedPtr<class FOnlineSessionSearch> SessionSearchSettings;
	FDelegateHandle LoginDelegateHandle;
	
	UPROPERTY(EditDefaultsOnly, Category = "Level", meta=(AllowPrivateAccess=true))
	TSoftObjectPtr<UWorld> SelectLevel;
	
	void LoginComleted(int NumOfPlayer, bool bSuccessful, const FUniqueNetId& UserID, const FString& Error);
	
	FDelegateHandle FindSessionsDelegateHandle;
	
	UFUNCTION()
	void OnFindSessionsCompleted(bool bWasSuccessful);
	
	void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	
	bool bShouldSkipLoginAndGoToLobby = false;
	
	UFUNCTION()
	void HandleNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);
};
