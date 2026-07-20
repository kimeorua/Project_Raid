// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/MMC/PR_InitAttributeCalculation.h"
#include "GameplayTagContainer.h"
#include "PR_GameplayTags.h"

#include "GAS/AttributeSet/PR_BasicAttributeSet.h"
#include "Utils/LogHelper.h"

UPR_InitAttributeCalculation::UPR_InitAttributeCalculation()
{
	BaseHPCaptureDef.AttributeToCapture = UPR_BasicAttributeSet::GetMaxSPAttribute();
	BaseHPCaptureDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	BaseHPCaptureDef.bSnapshot = false;
	
	RelevantAttributesToCapture.Add(BaseHPCaptureDef);
}

float UPR_InitAttributeCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* Source = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* Target = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Source;
	EvaluateParameters.TargetTags = Target;
	
	float MaxHP = 0.0f;
	GetCapturedAttributeMagnitude(BaseHPCaptureDef, Spec, EvaluateParameters, MaxHP);
	
	FGameplayTag RateTag = PR_GameplayTags::PR_Data_Rate_HP;
	
	float HPRate = Spec.GetSetByCallerMagnitude(RateTag, false, 1.0f);
	
	MaxHP = HPRate * 100;
	
	return MaxHP;
}