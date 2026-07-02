// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/PR_Weapon_Base.h"
#include "Components/StaticMeshComponent.h"

APR_Weapon_Base::APR_Weapon_Base()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetRootComponent());
	
	WeaponMesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	WeaponMesh->SetCollisionProfileName("NoCollision");
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APR_Weapon_Base::BeginPlay()
{
	Super::BeginPlay();
}