// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PR_PlayerCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Component/Weapon/PR_WeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GAS/ASC/PR_AbilitySystemComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Component/Input/PR_EnhancedInputComponent.h"

#include "PlayerState/PR_PlayerState.h"
#include "Subsystem/PR_AbilityInitSubsystem.h"
#include "DataAsset/PR_WeaponDataAsset.h"
#include "Weapon/PR_Weapon_Base.h"
#include "PR_GameplayTags.h"
#include "Component/UI/PR_UIComponent_Player.h"

#include "Utils/LogHelper.h"

APR_PlayerCharacter::APR_PlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 200.0f;
	SpringArmComponent->SocketOffset = FVector(0.0f, 20.0f, 80.0f);
	SpringArmComponent->bUsePawnControlRotation = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw   = false;
	bUseControllerRotationRoll  = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	UIComponent = CreateDefaultSubobject<UPR_UIComponent_Player>("Player UI Component");
}

void APR_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (PC->IsLocalController())
		{
			FInputModeGameOnly InputMode;
			PC->SetInputMode(InputMode);
			PC->bShowMouseCursor = false;
		}
	}
}

void APR_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (APR_PlayerState* TargetPlayerState = GetPlayerState<APR_PlayerState>())
	{
		PR_ASC->InitAbilityActorInfo(TargetPlayerState, this);
	}
	
	InitWeaponConfiguration();
	
	if (UIComponent)
	{
		UIComponent->InitComponent();
	}
}

void APR_PlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) { return; }

	ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();
	if (!LocalPlayer) { return; }

	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	if (SubSystem)
	{
		SubSystem->AddMappingContext(DefaultMappingContext, 0);
	}
	
	UPR_EnhancedInputComponent* PR_InputComp = Cast<UPR_EnhancedInputComponent>(PlayerInputComponent);
	
	if (!PR_InputComp || !InputDataAsset) { return; }
	
	PR_InputComp->BindNativeInputAction(InputDataAsset, PR_GameplayTags::PR_Input_Move, ETriggerEvent::Triggered, this, &ThisClass::InputMove);
	PR_InputComp->BindNativeInputAction(InputDataAsset, PR_GameplayTags::PR_Input_Look, ETriggerEvent::Triggered, this, &ThisClass::InputLook);
	PR_InputComp->BindAbilityInputAction(InputDataAsset, this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagReleased);
}

void APR_PlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	if (APR_PlayerState* TargetPlayerState = GetPlayerState<APR_PlayerState>())
	{
		PR_ASC->InitAbilityActorInfo(TargetPlayerState, this);
	}
	
	InitWeaponConfiguration();
	
	APlayerController* LocalPC = GetWorld() ? GetWorld()->GetFirstPlayerController() : nullptr;
	if (LocalPC && LocalPC->IsLocalController())
	{
		if (APR_PlayerCharacter* LocalChar = Cast<APR_PlayerCharacter>(LocalPC->GetPawn()))
		{
			if (UPR_UIComponent_Player* LocalUIComp = LocalChar->GetUIComponent()) // UIComponent 게터 사용
			{
				LocalUIComp->InitComponent();
				LocalUIComp->OtherPlayersUI_Create(LocalPC);
			}
		}
	}
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
	PlayerWeaponAnimLayerSetting(Type);
}

void APR_PlayerCharacter::InputMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotator(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

	if (MovementVector.Y != 0.0f)
	{
		const FVector ForwardDirection = MovementRotator.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.0f)
	{
		const FVector RightDirection = MovementRotator.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APR_PlayerCharacter::InputLook(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.0f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.0f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APR_PlayerCharacter::Input_AbilityInputTagPressed(FGameplayTag InInputTag)
{
	if (!IsLocallyControlled()) { return; }
	if (! InInputTag.IsValid()) { return; }
	PR_ASC->OnAbilityInputPressed(InInputTag);
}

void APR_PlayerCharacter::Input_AbilityInputTagReleased(FGameplayTag InInputTag)
{
	if (!IsLocallyControlled()) { return; }
	if (! InInputTag.IsValid()) { return; }
	PR_ASC->OnAbilityInputReleased(InInputTag);
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
		
		for (const FPR_InputAbilityConfig& Config : InitData->GetInputWeaponAbilities())
		{
			if (Config.AbilityClass)
			{
				FGameplayAbilitySpec AbilitySpec(Config.AbilityClass, 1, 0, this);

				if (Config.InputTag.IsValid())
				{
					AbilitySpec.GetDynamicSpecSourceTags().AddTag(Config.InputTag);
				}
				PR_ASC->GiveAbility(AbilitySpec);
			}
		}
		
		for (const TSubclassOf<UGameplayAbility>& AbilityClass : InitData->GetNonInputWeaponAbilities())
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

void APR_PlayerCharacter::PlayerWeaponAnimLayerSetting(EWeaponType InType)
{
	if (!GetMesh()) { return; }
	
	UPR_AbilityInitSubsystem* DataSubsystem = GetGameInstance()->GetSubsystem<UPR_AbilityInitSubsystem>();
	if (!DataSubsystem) { return; }
		
	const UPR_WeaponDataAsset* InitData = DataSubsystem->GetWeaponInitData(InType);
	if (!InitData ||!InitData->GetWeaponAnim()) { return; }
	
	GetMesh()->LinkAnimClassLayers(InitData->GetWeaponAnim());
}