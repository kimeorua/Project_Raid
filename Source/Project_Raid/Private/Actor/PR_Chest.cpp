// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PR_Chest.h"
#include "Components/StaticMeshComponent.h"

APR_Chest::APR_Chest()
{
	ChestBottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestBottom"));
 	ChestTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chest_Top"));
	SetRootComponent(ChestBottom);
	ChestTop->SetupAttachment(GetRootComponent());
}

void APR_Chest::BeginPlay()
{
	Super::BeginPlay();
}