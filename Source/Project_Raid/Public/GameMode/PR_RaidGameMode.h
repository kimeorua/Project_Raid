// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PR_RaidGameMode.generated.h"

class APR_Dummy;

UCLASS()
class PROJECT_RAID_API APR_RaidGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	APR_RaidGameMode();
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	int32 CurrentPlayerCount = 1;
	
	UPROPERTY()
	int32 DummyCount = 1;
	
	UPROPERTY(EditDefaultsOnly, Category = "Spawning", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<APR_Dummy> DummyClass;
	
	UPROPERTY()
	TArray<TObjectPtr<APR_Dummy>> SpawnedDummies;
	
	void SpawnDummiesForConnectedPlayers();
};