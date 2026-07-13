// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PR_UIComponent_Base.generated.h"

class APR_BaseCharacter;
class UPR_PlayerHUD;
class UAbilitySystemComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_RAID_API UPR_UIComponent_Base : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPR_UIComponent_Base();
	
	virtual void BeginPlay() override;
	
	void InitComponent(APR_BaseCharacter* BaseCharacter);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPR_PlayerHUD> HUDClass;
	
	UPROPERTY()
	TObjectPtr<UPR_PlayerHUD> HUD_Player;

	UPROPERTY()
	TObjectPtr <UAbilitySystemComponent>ASC;
};
