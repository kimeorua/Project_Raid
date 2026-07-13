// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PR_BaseCharacter.h"

#include "Component/UI/PR_UIComponent_Base.h"
#include "GAS/ASC/PR_AbilitySystemComponent.h"
#include "GAS/AttributeSet/PR_BasicAttributeSet.h"
#include "Component/Weapon/PR_WeaponComponent.h"

APR_BaseCharacter::APR_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PR_ASC = CreateDefaultSubobject<UPR_AbilitySystemComponent>(TEXT("PR_ASC"));
	PR_ASC->SetIsReplicated(true);
	PR_ASC->SetReplicationMode(ReplicationMode);
	
	BasicAttributeSet = CreateDefaultSubobject<UPR_BasicAttributeSet>(TEXT("BasicAttributeSet"));
	
	WeaponComponent = CreateDefaultSubobject<UPR_WeaponComponent>(TEXT("WeaponComponent"));
	
	UIComponent = CreateDefaultSubobject<UPR_UIComponent_Base>(TEXT("UIComponent"));
}

void APR_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APR_BaseCharacter::PossessedBy(AController* byController)
{
	Super::PossessedBy(byController);
	
	PR_ASC->InitAbilityActorInfo(this, this);
}

UAbilitySystemComponent* APR_BaseCharacter::GetAbilitySystemComponent() const
{
	return PR_ASC;
}
