// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Weapon/PR_WeaponComponent.h"

#include "Weapon/PR_Weapon_Base.h"

UPR_WeaponComponent::UPR_WeaponComponent()
{
}

void UPR_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
	WeaponContainer.Empty();
}

void UPR_WeaponComponent::SettingWeapon(EEquipType InEquipType, APR_Weapon_Base* InWeapon, USkeletalMeshComponent* MeshComp)
{
	if (WeaponContainer.Contains(InEquipType)) { return; }
	
	AActor* Owner = GetOwner();
	if (!Owner || !Owner->HasAuthority()) { return; }
	
	if (!WeaponContainer.Contains(InEquipType))
	{
		WeaponContainer.FindOrAdd(InEquipType) = InWeapon;
		InWeapon->SetOwner(Owner);
		
		InWeapon->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, InWeapon->GetAttachSocket());
	}
}
