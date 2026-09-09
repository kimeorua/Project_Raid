// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/AnimNotify/PR_ANS_ComboWindow.h"

#include "AbilitySystemBlueprintLibrary.h"
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
	
	if (AActor* Owner = MeshComp->GetOwner())
	{
		FGameplayEventData Payload;
        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, PR_GameplayTags::PlayerState_Combat_ComboWindow, Payload);
	}
}

void UPR_ANS_ComboWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	
	if (!MeshComp) { return; }
	
	if (AActor* Owner = MeshComp->GetOwner())
	{
		FGameplayEventData Payload;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, PR_GameplayTags::PlayerState_Combat_ComboWindow_Close, Payload);
	}
}
