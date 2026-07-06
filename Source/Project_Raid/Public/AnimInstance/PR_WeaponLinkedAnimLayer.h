// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/PR_AnimInstance_Base.h"
#include "PR_WeaponLinkedAnimLayer.generated.h"

class UPR_AnimInstance_Player;

UCLASS()
class PROJECT_RAID_API UPR_WeaponLinkedAnimLayer : public UPR_AnimInstance_Base
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UPR_AnimInstance_Player* GetPlayerAnimInstance() const;
};
