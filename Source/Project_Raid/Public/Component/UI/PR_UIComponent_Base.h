// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PR_UIComponent_Base.generated.h"

class UAbilitySystemComponent;
class APR_BaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_RAID_API UPR_UIComponent_Base : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPR_UIComponent_Base();
	virtual void BeginPlay() override;
	virtual void InitComponent();
	
protected:
	UPROPERTY()
	TObjectPtr <UAbilitySystemComponent>ASC;
	
	UPROPERTY()
	TObjectPtr<APR_BaseCharacter> OwnerCharacter;
};
