// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/AnimNotify/PR_ANS_ComboWindow.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "PR_GameplayTags.h"

UPR_ANS_ComboWindow::UPR_ANS_ComboWindow()
{
#if WITH_EDITOR
	NotifyColor = FColor(130, 80, 230, 255);
#endif
}

void UPR_ANS_ComboWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	if (!MeshComp) { return; }
	
	if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(MeshComp->GetOwner()))
	{
		ASC->AddLooseGameplayTag(PR_GameplayTags::PlayerState_Combat_ComboWindow);
	}
}

void UPR_ANS_ComboWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	
	if (!MeshComp) { return; }
	
	if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(MeshComp->GetOwner()))
	{
		ASC->RemoveLooseGameplayTag(PR_GameplayTags::PlayerState_Combat_ComboWindow);
	}
}
