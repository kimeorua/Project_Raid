// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/PR_AnimInstance_Base.h"

#include "KismetAnimationLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Character/PR_BaseCharacter.h"

void UPR_AnimInstance_Base::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	CashedCharacter = Cast<APR_BaseCharacter>(TryGetPawnOwner());

	if (CashedCharacter)
	{
		CashedMovementComponent = CashedCharacter->GetCharacterMovement();
	}
}

void UPR_AnimInstance_Base::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	if (!CashedCharacter || !CashedMovementComponent) { return; }
	Speed = CashedCharacter->GetVelocity().Size2D();
	bHasAcceleration = CashedMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.0f;
	Direction= UKismetAnimationLibrary::CalculateDirection(CashedCharacter->GetVelocity(), CashedCharacter->GetActorRotation());
}
