// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataAsset/PR_WeaponDataAsset.h"
#include "PR_AbilityInitSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_RAID_API UPR_AbilityInitSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	const UPR_WeaponDataAsset* GetWeaponInitData(EWeaponType InType) const;

private:
	UPROPERTY()
	TMap<EWeaponType, TObjectPtr<const UPR_WeaponDataAsset>> WeaponDataMap;
};
