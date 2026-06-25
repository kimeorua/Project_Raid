// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PR_BaseCharacter.h"

APR_BaseCharacter::APR_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APR_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APR_BaseCharacter::PossessedBy(AController* byController)
{
	Super::PossessedBy(byController);
}