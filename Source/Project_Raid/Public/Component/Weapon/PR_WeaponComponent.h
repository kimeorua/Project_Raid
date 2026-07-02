// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Type/Enums/PR_Enums.h"
#include "PR_WeaponComponent.generated.h"

class APR_Weapon_Base;
class USkeletalMeshComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_RAID_API UPR_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TMap<EEquipType, TObjectPtr<APR_Weapon_Base>> WeaponContainer;
	
public:	
	UPR_WeaponComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	void SettingWeapon(EEquipType InEquipType, APR_Weapon_Base* InWeapon, USkeletalMeshComponent* MeshComp);
};
