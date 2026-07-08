// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/PR_InputDataAsset.h"
#include "PR_EnhancedInputComponent.generated.h"

UCLASS()
class PROJECT_RAID_API UPR_EnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserObject, typename CallbackFunc>
	inline void BindNativeInputAction(const UPR_InputDataAsset* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);

	template<class UserObject, typename CallbackFunc>
	inline void BindAbilityInputAction(const UPR_InputDataAsset* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc);
};

template <class UserObject, typename CallbackFunc>
void UPR_EnhancedInputComponent::BindNativeInputAction(const UPR_InputDataAsset* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent,
	UserObject* ContextObject, CallbackFunc Func)
{
	if (!InInputConfig) return;
	
	if (const UInputAction* IA = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(IA, TriggerEvent, ContextObject, Func);
	}
}

template <class UserObject, typename CallbackFunc>
void UPR_EnhancedInputComponent::BindAbilityInputAction(const UPR_InputDataAsset* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc,
	CallbackFunc InputReleasedFunc)
{
	if (!InInputConfig) {return;}
	for (const FPR_InputActionConfig& ActionConfig : InInputConfig->AbilityInputActions)
	{
		if (ActionConfig.IsValid())
		{
			if (InputPressedFunc)
			{
				BindAction(ActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, ActionConfig.InputTag);
			}
			if (InputReleasedFunc)
			{
				BindAction(ActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc, ActionConfig.InputTag);
			}
		}
	}
}