// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Type/Enums/PR_Enums.h"
#include "PR_WeaponDataAsset.generated.h"

class UGameplayAbility;
class APR_Weapon_Base;
class UPR_WeaponLinkedAnimLayer;

UCLASS()
class PROJECT_RAID_API UPR_WeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset", meta = (AllowPrivateAccess = true))
	EWeaponType Type = EWeaponType::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<UGameplayAbility>> GiveToAbilities;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<APR_Weapon_Base>> Weapons;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Animation", meta = (AllowPrivateAccess = true))
	TSubclassOf<UAnimInstance> WeaponAnimBlueprintClass;
	
public:
	FORCEINLINE EWeaponType GetWeaponType() const { return Type; }
	FORCEINLINE const TArray<TSubclassOf<UGameplayAbility>>& GetGiveToAbilities() const { return GiveToAbilities; }
	FORCEINLINE const TArray<TSubclassOf<APR_Weapon_Base>>& GetWeapons() const { return Weapons; }
	FORCEINLINE  TSubclassOf<UAnimInstance> GetWeaponAnim() const { return WeaponAnimBlueprintClass;}
};
