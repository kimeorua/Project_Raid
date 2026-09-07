// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "PR_ANS_ComboWindow.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "PR Combo Window"))
class PROJECT_RAID_API UPR_ANS_ComboWindow : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UPR_ANS_ComboWindow();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
