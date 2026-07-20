// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "PR_InitAttributeCalculation.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_RAID_API UPR_InitAttributeCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UPR_InitAttributeCalculation();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition BaseHPCaptureDef;
};
