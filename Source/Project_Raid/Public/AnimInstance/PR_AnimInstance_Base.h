// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PR_AnimInstance_Base.generated.h"

class APR_BaseCharacter;
class UCharacterMovementComponent;

UCLASS()
class PROJECT_RAID_API UPR_AnimInstance_Base : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds)override;
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomationData")
	float Speed;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomationData")
	float Direction;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomationData")
	bool bHasAcceleration;
	
	UPROPERTY()
	TObjectPtr<APR_BaseCharacter> CashedCharacter;
	
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> CashedMovementComponent;
};
