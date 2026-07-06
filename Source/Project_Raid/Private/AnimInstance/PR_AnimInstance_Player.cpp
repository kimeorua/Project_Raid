// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/PR_AnimInstance_Player.h"

#include "Character/PR_PlayerCharacter.h"

void UPR_AnimInstance_Player::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	if (CashedCharacter)
	{
		CashedPlayerCharacter = Cast<APR_PlayerCharacter>(CashedCharacter);
	}
}

void UPR_AnimInstance_Player::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}
