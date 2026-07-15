// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/UI/PR_UIComponent_Base.h"
#include "PR_UIComponent_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_RAID_API UPR_UIComponent_Enemy : public UPR_UIComponent_Base
{
	GENERATED_BODY()
public:
	UPR_UIComponent_Enemy();
	virtual void BeginPlay() override;
	virtual void InitComponent() override;
};
