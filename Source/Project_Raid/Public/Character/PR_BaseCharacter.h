// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "PR_BaseCharacter.generated.h"

class UPR_AbilitySystemComponent;
class UPR_BasicAttributeSet;
class UPR_WeaponComponent;

UCLASS()
class PROJECT_RAID_API APR_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APR_BaseCharacter();
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* byController) override;
	
	//----------------ASC--------------//
private:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS/ASC", meta = (AllowPrivateAccess = "true"))
	EGameplayEffectReplicationMode ReplicationMode = EGameplayEffectReplicationMode::Mixed;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS/ASC", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPR_AbilitySystemComponent> PR_ASC;
	
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	//--------------------AttributeSet-----------------------//
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS/AttributeSet", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPR_BasicAttributeSet> BasicAttributeSet;	
	
	//--------------------Weapon Component-----------------------//
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponComponent",meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPR_WeaponComponent> WeaponComponent;
};
