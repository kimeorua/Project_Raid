// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/PR_Ability_Base.h"
#include "PR_Ability_Player.generated.h"

class APR_PlayerCharacter;

UCLASS()
class PROJECT_RAID_API UPR_Ability_Player : public UPR_Ability_Base
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category="Abilities|Util")
	APR_PlayerCharacter* GetPR_PlayerCharacter() const;
	
	UFUNCTION(BlueprintPure, Category = "Clash|Ability|Util", meta = (DeterminesOutputType = "ComponentClass"))
	UActorComponent* GetPR_PlayerCharacterComponent(TSubclassOf<UActorComponent> ComponentClass) const;
};
