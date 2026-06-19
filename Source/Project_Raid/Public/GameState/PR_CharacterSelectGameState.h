// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PR_CharacterSelectGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLobbyRefreshRequired);

UCLASS()
class PROJECT_RAID_API APR_CharacterSelectGameState : public AGameState
{
	GENERATED_BODY()
public:
	virtual void AddPlayerState(APlayerState* PlayerState) override;
	virtual void RemovePlayerState(APlayerState* PlayerState) override;
	
	UPROPERTY(BlueprintAssignable, Category = "PR|Delegates")
	FOnLobbyRefreshRequired OnLobbyRefreshRequired;
	
	void StartGame(const FString& GameLV_Name);
};
