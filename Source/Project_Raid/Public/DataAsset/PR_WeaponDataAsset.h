// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Type/Enums/PR_Enums.h"
#include "Type/Structs/PR_Structs.h"
#include "PR_WeaponDataAsset.generated.h"

class UGameplayAbility;
class APR_Weapon_Base;
class UPR_WeaponLinkedAnimLayer;
class UPR_WeaponCombatUI;

UCLASS()
class PROJECT_RAID_API UPR_WeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset", meta = (AllowPrivateAccess = true))
	EWeaponType Type = EWeaponType::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset", meta = (AllowPrivateAccess = true))
	TArray<FPR_InputAbilityConfig> InputWeaponAbilities;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<UGameplayAbility>> NonInputWeaponAbilities;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<APR_Weapon_Base>> Weapons;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Animation", meta = (AllowPrivateAccess = true))
	TSubclassOf<UAnimInstance> WeaponAnimBlueprintClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AttributeSet", meta = (AllowPrivateAccess = true))
	FPR_InitAttributeConfig InitAttributeConfig;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponUI", meta = (AllowPrivateAccess = true))
	TSubclassOf<UPR_WeaponCombatUI> WeaponCombatUIClass;
	
public:
	FORCEINLINE EWeaponType GetWeaponType() const { return Type; }
	FORCEINLINE const TArray<FPR_InputAbilityConfig>& GetInputWeaponAbilities() const { return InputWeaponAbilities; }
	FORCEINLINE const TArray<TSubclassOf<UGameplayAbility>>& GetNonInputWeaponAbilities() const { return NonInputWeaponAbilities; }
	FORCEINLINE const TArray<TSubclassOf<APR_Weapon_Base>>& GetWeapons() const { return Weapons; }
	FORCEINLINE  TSubclassOf<UAnimInstance> GetWeaponAnim() const { return WeaponAnimBlueprintClass;}
	FORCEINLINE FPR_InitAttributeConfig GetInitAttributeConfig() const { return InitAttributeConfig; }
	FORCEINLINE TSubclassOf<UPR_WeaponCombatUI> GetWeaponCombatUIClass() const { return WeaponCombatUIClass; }
};
