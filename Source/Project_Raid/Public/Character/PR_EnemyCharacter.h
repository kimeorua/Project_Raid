// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PR_BaseCharacter.h"
#include "PR_EnemyCharacter.generated.h"

class UPR_UIComponent_Enemy;

UCLASS()
class PROJECT_RAID_API APR_EnemyCharacter : public APR_BaseCharacter
{
	GENERATED_BODY()
	//--------------------Basic--------------------//
public:
	APR_EnemyCharacter();
	
	//--------------------UI Component-----------------------//
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UIComponent",meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPR_UIComponent_Enemy> UIComponent;
};
