// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PR_Dummy.h"

#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"


APR_Dummy::APR_Dummy()
{
	DummyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DummyMesh"));
	DummyCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("DummyCollision"));
	SetRootComponent(DummyCollision);
	DummyMesh->SetupAttachment(GetRootComponent());
	
	ChestOffset = CreateDefaultSubobject<USceneComponent>(TEXT("ChestOffset"));
	ChestOffset->SetupAttachment(GetRootComponent());
}

FTransform APR_Dummy::GetChestTransform()
{
	if (!ChestOffset) { return FTransform::Identity; }
	return ChestOffset->GetComponentTransform();
}

void APR_Dummy::BeginPlay()
{
	Super::BeginPlay();
}
