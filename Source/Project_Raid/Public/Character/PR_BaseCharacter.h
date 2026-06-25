// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PR_BaseCharacter.generated.h"

UCLASS()
class PROJECT_RAID_API APR_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APR_BaseCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* byController) override;
};
