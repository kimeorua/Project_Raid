// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Type/Enums/PR_Enums.h"
#include "PR_WeaponDataAsset.generated.h"

class UGameplayAbility;

UCLASS()
class PROJECT_RAID_API UPR_WeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset", meta = (AllowPrivateAccess = true))
	EWeaponType Type = EWeaponType::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<UGameplayAbility>> GiveToAbilities;
	
public:
	FORCEINLINE EWeaponType GetWeaponType() const { return Type; }
	FORCEINLINE const TArray<TSubclassOf<UGameplayAbility>>& GetGiveToAbilities() const { return GiveToAbilities; }
};
