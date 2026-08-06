// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PR_InteractableActor_Base.h"

#include "Net/UnrealNetwork.h"

APR_InteractableActor_Base::APR_InteractableActor_Base()
{
	bReplicates = true;
}

void APR_InteractableActor_Base::BeginPlay()
{
	Super::BeginPlay();
}

void APR_InteractableActor_Base::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(APR_InteractableActor_Base, RequiredPlayerIndexTag);
}

