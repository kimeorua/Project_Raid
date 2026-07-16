// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PR_GameState_BattelState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPartyHPChanged, int32, TargetID, float, NewPercent);

UCLASS()
class PROJECT_RAID_API APR_GameState_BattelState : public AGameState
{
	GENERATED_BODY()
public:
	FOnPartyHPChanged OnPartyHPChanged;
};