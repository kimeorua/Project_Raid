// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/PR_AnimInstance_Enemy.h"

#include "Character/PR_EnemyCharacter.h"

void UPR_AnimInstance_Enemy::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	if (CashedCharacter)
	{
		CashedEnemyCharacter = Cast<APR_EnemyCharacter>(CashedCharacter);
	}
}

void UPR_AnimInstance_Enemy::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}
