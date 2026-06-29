// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PR_PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GAS/ASC/PR_AbilitySystemComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "PlayerState/PR_PlayerState.h"

#include "Utils/LogHelper.h"

APR_PlayerCharacter::APR_PlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 200.0f;
	SpringArmComponent->SocketOffset = FVector(0.0f, 20.0f, 80.0f);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
}

void APR_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APR_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (APR_PlayerState* TargetPlayerState = GetPlayerState<APR_PlayerState>())
	{
		PR_ASC->InitAbilityActorInfo(TargetPlayerState, this);
	}
	
	InitWeaponConfiguration();
}

void APR_PlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	PR_ASC->InitAbilityActorInfo(PR_PlayerState, this);
	
	InitWeaponConfiguration();
}

void APR_PlayerCharacter::InitWeaponConfiguration()
{
	if (PR_PlayerState) return;
	
	APR_PlayerState* TargetPlayerState = GetPlayerState<APR_PlayerState>();
    
	if (!TargetPlayerState) { return; }
	PR_PlayerState = TargetPlayerState;
    
	EWeaponType Type = PR_PlayerState->GetWeaponType();
	
	switch (Type)
	{
	case EWeaponType::SwordShield:
		PlayerColorInitialization(FLinearColor::White);
		break;
	case EWeaponType::DualSword:
		PlayerColorInitialization(FLinearColor::Blue);
		break;
	case EWeaponType::Lance:
		PlayerColorInitialization(FLinearColor::Yellow);
		break;
	case EWeaponType::Katana:
		PlayerColorInitialization(FLinearColor::Red);
		break;
	default:
		break;
	}
}

void APR_PlayerCharacter::PlayerColorInitialization(FLinearColor NewColor)
{
	if (!GetMesh()) return;
	
	const int32 NumMaterials = GetMesh()->GetNumMaterials();

	for (int32 ElementIndex = 0; ElementIndex < NumMaterials; ++ElementIndex)
	{
		UMaterialInstanceDynamic* DynamicMat = GetMesh()->CreateDynamicMaterialInstance(ElementIndex);
        
		if (DynamicMat)
		{
			DynamicMat->SetVectorParameterValue(TEXT("Color"), NewColor);
		}
	}
}
