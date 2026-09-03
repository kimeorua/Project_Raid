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
	
	if (const TObjectPtr<UPR_ComboAttackDataAsset>* FoundAsset = Settings->CachedWeaponDataMap.Find(InWeaponType)) {return *FoundAsset; }
	
	if (const TSoftObjectPtr<UPR_ComboAttackDataAsset>* SoftPtr = Settings->WeaponDataMap.Find(InWeaponType))
	{
		if (UPR_ComboAttackDataAsset* LoadedAsset = SoftPtr->LoadSynchronous())
		{
			const_cast<UPR_ComboAttackDeveloperSetting*>(Settings)->CachedWeaponDataMap.Add(InWeaponType, LoadedAsset);
			return LoadedAsset;
		}
	}
	return nullptr;
}

void UPR_ComboAttackDeveloperSetting::PreloadAllWeaponData()
{
	const UPR_ComboAttackDeveloperSetting* Settings = GetDefault<UPR_ComboAttackDeveloperSetting>();
	if (!Settings) { return; }

	for (const auto& Data : Settings->WeaponDataMap)
	{
		EWeaponType WeaponType = Data.Key;
		const TSoftObjectPtr<UPR_ComboAttackDataAsset>& SoftPtr = Data.Value;

		if (!Settings->CachedWeaponDataMap.Contains(WeaponType) && !SoftPtr.IsNull())
		{
			if (UPR_ComboAttackDataAsset* LoadedAsset = SoftPtr.LoadSynchronous())
			{
				const_cast<UPR_ComboAttackDeveloperSetting*>(Settings)->CachedWeaponDataMap.Add(WeaponType, LoadedAsset);
			}
		}
	}
}
