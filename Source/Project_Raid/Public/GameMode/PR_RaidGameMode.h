// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PR_RaidGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_RAID_API APR_RaidGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	APR_RaidGameMode();
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	
private:
	UPROPERTY()
	int32 CurrentPlayerCount = 1;
};
