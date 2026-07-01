// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DataAsset/PR_WeaponDataAsset.h"
#include "PR_DataAssetDeveloperSettings.generated.h"

UCLASS(Config=Game, defaultconfig, meta = (DisplayName = "Project Raid DataAsset Settings"))
class PROJECT_RAID_API UPR_DataAssetDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(Config, EditAnywhere, Category = "Weapon Data")
	TMap<EWeaponType, TSoftObjectPtr<UPR_WeaponDataAsset>> WeaponDataMap;
};
