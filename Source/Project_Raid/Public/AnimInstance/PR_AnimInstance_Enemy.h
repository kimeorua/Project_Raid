// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/PR_AnimInstance_Base.h"
#include "PR_AnimInstance_Enemy.generated.h"

class APR_EnemyCharacter;

UCLASS()
class PROJECT_RAID_API UPR_AnimInstance_Enemy : public UPR_AnimInstance_Base
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds)override;
	
protected:
	UPROPERTY()
	TObjectPtr<APR_EnemyCharacter> CashedEnemyCharacter;
};
