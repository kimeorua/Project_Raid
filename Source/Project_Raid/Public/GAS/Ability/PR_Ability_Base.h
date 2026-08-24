// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PR_Ability_Base.generated.h"

class UPR_AbilitySystemComponent;
class APR_BaseCharacter;

UCLASS()
class PROJECT_RAID_API UPR_Ability_Base : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category="Abilities|Util")
	UPR_AbilitySystemComponent* GetPR_ASC() const;
	
	UFUNCTION(BlueprintPure, Category="Abilities|Util")
	APR_BaseCharacter* GetPR_BaseCharacter() const;
	
	UFUNCTION(BlueprintPure, Category = "Clash|Ability|Util", meta = (DeterminesOutputType = "ComponentClass"))
	UActorComponent* GetPR_BaseCharacterComponent(TSubclassOf<UActorComponent> ComponentClass) const;
};
