// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PR_BaseCharacter.h"
#include "Type/Enums/PR_Enums.h"
#include "InputActionValue.h"
#include "PR_PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class APR_PlayerState;
class APR_Weapon_Base;
class UInputMappingContext;
class UPR_InputDataAsset;
class UPR_UIComponent_Player;
class UPR_WeaponDataAsset;
class UInputComponent;

UCLASS()
class PROJECT_RAID_API APR_PlayerCharacter : public APR_BaseCharacter
{
	GENERATED_BODY()

//--------------------Basic--------------------//
public:
	APR_PlayerCharacter();
	virtual void OnRep_PlayerState() override;
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	
//--------------------PlayerState--------------------//
private:
	UPROPERTY()
	TObjectPtr<APR_PlayerState> PR_PlayerState;
	
//---------------------Weapon--------------------//
private:
	void PlayerColorInitialization(FLinearColor NewColor);
	void PlayerColorSettings(EWeaponType InType);
	void PlayerWeaponAndAbilityInitialization(EWeaponType InType);
	void PlayerWeaponInitialization(const TArray<TSubclassOf<APR_Weapon_Base>>& InWeapons);
	void PlayerWeaponAnimLayerSetting(const UPR_WeaponDataAsset* InitData);
	
public:
	void InitWeaponConfiguration();
	
//---------------------Input--------------------//
private:
	UPROPERTY(EditDefaultsOnly, Category = "IMC", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "IMC", meta = (AllowPrivateAccess = true))
	TObjectPtr<UPR_InputDataAsset> InputDataAsset;
	
	float LockedMovementYaw = 0.0f;
	bool bIsMoving = false;
	
	void InputMove(const FInputActionValue& InputActionValue);
	void InputLook(const FInputActionValue& InputActionValue);
	
	void Input_AbilityInputTagPressed(FGameplayTag InInputTag);
	void Input_AbilityInputTagReleased(FGameplayTag InInputTag);
	
	//--------------------UI Component-----------------------//
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UIComponent",meta = (AllowPrivateAccess = true))
	TObjectPtr<UPR_UIComponent_Player> UIComponent;
	
public:
	FORCEINLINE UPR_UIComponent_Player* GetUIComponent() const { return UIComponent; };
	
	//---------------------Attribute--------------------//
private:
	void SettingInitAttributes(const UPR_WeaponDataAsset* InitData);
	
	//---------------------Tag--------------------//
private:
	UPROPERTY(Replicated)
	FGameplayTag PlayerIndexTag;
	
public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE FGameplayTag GetPlayerIndexTag() const { return PlayerIndexTag; }
	void SetPlayerIndexTag(const FGameplayTag& InTag) { PlayerIndexTag = InTag; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
