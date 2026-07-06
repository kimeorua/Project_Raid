// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PR_BaseCharacter.h"
#include "Type/Enums/PR_Enums.h"
#include "PR_PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class APR_PlayerState;
class APR_Weapon_Base;

UCLASS()
class PROJECT_RAID_API APR_PlayerCharacter : public APR_BaseCharacter
{
	GENERATED_BODY()

//--------------------Basic--------------------//
public:
	APR_PlayerCharacter();
	virtual void OnRep_PlayerState() override;
	
protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	
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
	void PlayerWeaponAnimLayerSetting(EWeaponType InType);
	
public:
	void InitWeaponConfiguration();
};
