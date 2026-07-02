// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PR_PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Component/Weapon/PR_WeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GAS/ASC/PR_AbilitySystemComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "PlayerState/PR_PlayerState.h"
#include "Subsystem/PR_AbilityInitSubsystem.h"
#include "DataAsset/PR_WeaponDataAsset.h"
#include "Weapon/PR_Weapon_Base.h"

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
	
	if (APR_PlayerState* TargetPlayerState = GetPlayerState<APR_PlayerState>())
	{
		PR_ASC->InitAbilityActorInfo(TargetPlayerState, this);
	}
	
	InitWeaponConfiguration();
}

void APR_PlayerCharacter::InitWeaponConfiguration()
{
	if (PR_PlayerState) { return; }
	
	APR_PlayerState* TargetPlayerState = GetPlayerState<APR_PlayerState>();
    
	if (!TargetPlayerState) { return; }
	PR_PlayerState = TargetPlayerState;
    
	EWeaponType Type = PR_PlayerState->GetWeaponType();
	
	PlayerColorSettings(Type);
	PlayerWeaponAndAbilityInitialization(Type);
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

void APR_PlayerCharacter::PlayerColorSettings(EWeaponType InType)
{
	switch (InType)
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

void APR_PlayerCharacter::PlayerWeaponAndAbilityInitialization(EWeaponType InType)
{
	if (HasAuthority() && PR_ASC)
	{
		UPR_AbilityInitSubsystem* DataSubsystem = GetGameInstance()->GetSubsystem<UPR_AbilityInitSubsystem>();
		if (!DataSubsystem) { return; }
		
		const UPR_WeaponDataAsset* InitData = DataSubsystem->GetWeaponInitData(InType);
		if (!InitData) { return; }
		
		PlayerWeaponInitialization(InitData->GetWeapons());
		
		const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToGive = InitData->GetGiveToAbilities();
		
		for (const TSubclassOf<UGameplayAbility>& AbilityClass : AbilitiesToGive)
		{
			if (AbilityClass)
			{
				PR_ASC->GiveAbility(FGameplayAbilitySpec(AbilityClass, 1, 0, this));
			}
		}
	}
}

void APR_PlayerCharacter::PlayerWeaponInitialization(const TArray<TSubclassOf<APR_Weapon_Base>>& InWeapons)
{
	if (!HasAuthority()) { return; }
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	for (TSubclassOf<APR_Weapon_Base> NewWeapon : InWeapons)
	{
		APR_Weapon_Base* SpawnedWeapon = GetWorld()->SpawnActor<APR_Weapon_Base> (NewWeapon, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		WeaponComponent->SettingWeapon(SpawnedWeapon->GetEquipType(), SpawnedWeapon, GetMesh());
	}
}
