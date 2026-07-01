// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/PR_AbilityInitSubsystem.h"

#include "DeveloperSetting/PR_DataAssetDeveloperSettings.h"

void UPR_AbilityInitSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	const UPR_DataAssetDeveloperSettings* DeveloperSettings_DA = GetDefault<UPR_DataAssetDeveloperSettings>();
	if (DeveloperSettings_DA)
	{
		for (const auto& Pair : DeveloperSettings_DA->WeaponDataMap)
		{
			if (const UPR_WeaponDataAsset* LoadedData = Pair.Value.LoadSynchronous())
			{
				WeaponDataMap.Add(Pair.Key, LoadedData);
			}
		}
	}
}

void UPR_AbilityInitSubsystem::Deinitialize()
{
	WeaponDataMap.Empty();
	
	Super::Deinitialize();
}

const UPR_WeaponDataAsset* UPR_AbilityInitSubsystem::GetWeaponInitData(EWeaponType InType) const
{
	return WeaponDataMap.Contains(InType) ? WeaponDataMap[InType] : nullptr;
}
