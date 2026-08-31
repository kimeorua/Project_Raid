// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Type/Enums/PR_Enums.h"
#include "PR_ComboAttackDeveloperSetting.generated.h"

class UPR_ComboAttackDataAsset;

UCLASS(Config=Game, defaultconfig, meta = (DisplayName = "Project Raid Comboattack DataAsset Settings"))
class PROJECT_RAID_API UPR_ComboAttackDeveloperSetting : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPR_ComboAttackDeveloperSetting();
	
	UFUNCTION(BlueprintPure, Category = "Combat|ComboAttack Developer Settings")
	static const UPR_ComboAttackDataAsset* GetWeaponDataAsset(EWeaponType InWeaponType);
	
protected:
	UPROPERTY(EditAnywhere, Config, Category = "Weapon Registry")
	TMap<EWeaponType, TSoftObjectPtr<UPR_ComboAttackDataAsset>> WeaponDataMap;
	
	UPROPERTY(Transient)
	mutable TMap<EWeaponType, TObjectPtr<UPR_ComboAttackDataAsset>> CachedWeaponDataMap;
};
