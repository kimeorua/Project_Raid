// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PR_WeaponCombatUI.generated.h"

class USizeBox;
class UImage;

UCLASS()
class PROJECT_RAID_API UPR_WeaponCombatUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	
	UPROPERTY(BlueprintReadOnly, Category = "WeaponCombatUI|Widgets", meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	float Width = 300.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	float Height = 300.0f;
};
