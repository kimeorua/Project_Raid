// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Type/Structs/PR_Structs.h"
#include "PR_InputDataAsset.generated.h"

class UInputAction;

UCLASS()
class PROJECT_RAID_API UPR_InputDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TArray<FPR_InputActionConfig> NativeInputActions;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TArray<FPR_InputActionConfig> AbilityInputActions;
	
	const UInputAction* FindNativeInputActionByTag(const FGameplayTag& InputTag) const;
};