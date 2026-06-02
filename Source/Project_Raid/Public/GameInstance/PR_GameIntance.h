// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "PR_GameIntance.generated.h"

class IOnlineSubsystem;

UCLASS()
class PROJECT_RAID_API UPR_GameIntance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
    void Login();
	
protected:
	virtual  void Init() override;
	virtual void Shutdown() override;
	
private:
	IOnlineSubsystem* OnlineSubsystem;
	IOnlineIdentityPtr IdentityPtr;
	
	FDelegateHandle LoginDelegateHandle;
	void LoginComleted(int NumOfPlayer, bool bSuccessful, const FUniqueNetId& UserID, const FString& Error);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Levels", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UWorld> LobbyLevelRef;
	
	void MoveToLobby() const;
};
