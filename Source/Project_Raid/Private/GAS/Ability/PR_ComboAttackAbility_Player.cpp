// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/PR_ComboAttackAbility_Player.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

#include "DeveloperSetting/PR_ComboAttackDeveloperSetting.h"
#include "PR_GameplayTags.h"

UPR_ComboAttackAbility_Player::UPR_ComboAttackAbility_Player()
{
	CurrentComboTag = FGameplayTag::EmptyTag;
	BufferedInputTag = FGameplayTag::EmptyTag;
	bIsComboWindowOpen = false;
}

void UPR_ComboAttackAbility_Player::ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
                                                    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!ASC)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	WeaponDataAsset = UPR_ComboAttackDeveloperSetting::GetWeaponDataAsset(WeaponType);
	if (!WeaponDataAsset)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	FGameplayTag ComboWindowTag = PR_GameplayTags::PlayerState_Combat_ComboWindow;
	TagDelegateHandle = ASC->RegisterGameplayTagEvent(ComboWindowTag, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &UPR_ComboAttackAbility_Player::OnComboWindowTagChanged);
	
	FGameplayTag InitialInputTag = GetBoundInputTag();
	
	const FPR_ComboNode* FirstNode = WeaponDataAsset->FindComboNode(CurrentComboTag, InitialInputTag);
		
	if (FirstNode)
	{
		ExecuteComboNode(*FirstNode);
	}
	else
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
}

void UPR_ComboAttackAbility_Player::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo())
	{
		FGameplayTag ComboWindowTag = PR_GameplayTags::PlayerState_Combat_ComboWindow;
		ASC->RegisterGameplayTagEvent(ComboWindowTag, EGameplayTagEventType::NewOrRemoved).Remove(TagDelegateHandle);
	}
	
	CurrentComboTag = FGameplayTag::EmptyTag;
	BufferedInputTag = FGameplayTag::EmptyTag;
	bIsComboWindowOpen = false;
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UPR_ComboAttackAbility_Player::ExecuteComboNode(const FPR_ComboNode& Node)
{
	CurrentComboTag = Node.NextComboTag;
	BufferedInputTag = FGameplayTag::EmptyTag;
	bIsComboWindowOpen = false;
	
	UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this,
		NAME_None,
		Node.ActionMontage,
		1.0f,
		NAME_None,
		false
	);

	if (MontageTask)
	{
		MontageTask->OnCompleted.AddDynamic(this, &UPR_ComboAttackAbility_Player::OnMontageEnded);
		MontageTask->OnInterrupted.AddDynamic(this, &UPR_ComboAttackAbility_Player::OnMontageEnded);
		MontageTask->OnCancelled.AddDynamic(this, &UPR_ComboAttackAbility_Player::OnMontageEnded);
		MontageTask->ReadyForActivation();
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}

void UPR_ComboAttackAbility_Player::OnComboWindowTagChanged(FGameplayTag Tag, int32 NewCount)
{
	bIsComboWindowOpen = (NewCount > 0);
	
	if (!bIsComboWindowOpen)
	{
		if (BufferedInputTag.IsValid() && WeaponDataAsset)
		{
			const FPR_ComboNode* NextNode = WeaponDataAsset->FindComboNode(CurrentComboTag, BufferedInputTag);
			if (NextNode)
			{
				ExecuteComboNode(*NextNode);
			}
		}
	}
}

void UPR_ComboAttackAbility_Player::OnMontageEnded()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

FGameplayTag UPR_ComboAttackAbility_Player::GetBoundInputTag() const
{
	if (const FGameplayAbilitySpec* Spec = GetCurrentAbilitySpec())
	{
		for (const FGameplayTag& Tag : Spec->GetDynamicSpecSourceTags())
		{
			if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("PR"))))
			{
				return Tag;
			}
		}
	}
	return FGameplayTag::EmptyTag;
}

void UPR_ComboAttackAbility_Player::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	
	if (bIsComboWindowOpen) { BufferedInputTag = GetBoundInputTag(); }
}