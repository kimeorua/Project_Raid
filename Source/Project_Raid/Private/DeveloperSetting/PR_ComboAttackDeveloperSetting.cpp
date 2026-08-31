// Fill out your copyright notice in the Description page of Project Settings.


#include "DeveloperSetting/PR_ComboAttackDeveloperSetting.h"
#include "DataAsset/PR_ComboAttackDataAsset.h"

UPR_ComboAttackDeveloperSetting::UPR_ComboAttackDeveloperSetting()
{
	CategoryName = TEXT("Game");
	SectionName = TEXT("WeaponSettings");
}

const UPR_ComboAttackDataAsset* UPR_ComboAttackDeveloperSetting::GetWeaponDataAsset(EWeaponType InWeaponType)
{
	const UPR_ComboAttackDeveloperSetting* Settings = GetDefault<UPR_ComboAttackDeveloperSetting>();
	if (!Settings) { return nullptr; }
	
	if (Settings->CachedWeaponDataMap.Contains(InWeaponType))
	{
		return Settings->CachedWeaponDataMap[InWeaponType];
	}
	
	if (const TSoftObjectPtr<UPR_ComboAttackDataAsset>* SoftPtr = Settings->WeaponDataMap.Find(InWeaponType))
	{
		UPR_ComboAttackDataAsset* LoadedAsset = SoftPtr->LoadSynchronous();
		if (LoadedAsset)
		{
			const_cast<UPR_ComboAttackDeveloperSetting*>(Settings)->CachedWeaponDataMap.Add(InWeaponType, LoadedAsset);
			return LoadedAsset;
		}
	}

	return nullptr;
}
