// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PR_BaseCharacter.h"
#include "GAS/ASC/PR_AbilitySystemComponent.h"
#include "GAS/AttributeSet/PR_BasicAttributeSet.h"

APR_BaseCharacter::APR_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PR_ASC = CreateDefaultSubobject<UPR_AbilitySystemComponent>(TEXT("PR_ASC"));
	PR_ASC->SetIsReplicated(true);
	PR_ASC->SetReplicationMode(ReplicationMode);
	
	BasicAttributeSet = CreateDefaultSubobject<UPR_BasicAttributeSet>(TEXT("BasicAttributeSet"));
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
