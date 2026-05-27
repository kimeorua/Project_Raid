// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PR_OptionSaveGame.generated.h"


UCLASS()
class PROJECT_RAID_API UPR_OptionSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float SavedVolume = 1.0f;
};
