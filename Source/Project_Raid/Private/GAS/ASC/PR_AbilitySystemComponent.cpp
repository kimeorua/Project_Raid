// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ASC/PR_AbilitySystemComponent.h"

void UPR_AbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (! InInputTag.IsValid()) { return; }
	
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.DynamicAbilityTags.HasTagExact(InInputTag))
		{
			Spec.InputPressed = true;
			
			if (Spec.IsActive())
			{
				AbilitySpecInputPressed(Spec);
			}
			else
			{
				TryActivateAbility(Spec.Handle);
			}
		}
	}
}

void UPR_AbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (! InInputTag.IsValid()) { return; }
	
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.DynamicAbilityTags.HasTagExact(InInputTag))
		{
			Spec.InputPressed = false;
			
			if (Spec.IsActive())
			{
				AbilitySpecInputReleased(Spec);
			}
		}
	}
}
