// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h"
#include "PR_Structs.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct  FPR_InputAbilityConfig
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GAS", meta = (Categories = "PR"))
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TSubclassOf<UGameplayAbility> AbilityClass;
	
	bool IsValid() const
	{
		return InputTag.IsValid() && (AbilityClass != nullptr);
	}
};

USTRUCT(BlueprintType)
struct FPR_InputActionConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UInputAction> InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS", meta = (Categories = "PR"))
	FGameplayTag InputTag;

	bool IsValid() const
	{
		return InputTag.IsValid() && (InputAction != nullptr);
	}
};