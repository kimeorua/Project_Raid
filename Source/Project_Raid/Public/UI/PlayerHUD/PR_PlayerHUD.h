// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PR_PlayerHUD.generated.h"

class UVerticalBox;
class UPR_ProgressBar;

UCLASS()
class PROJECT_RAID_API UPR_PlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadOnly, Category = "HUD|Widgets", meta = (BindWidget))
	TObjectPtr<UPR_ProgressBar> Player_HP_Bar;
	
	UPROPERTY(BlueprintReadOnly, Category = "HUD|Widgets", meta = (BindWidget))
	TObjectPtr<UVerticalBox> OtherPlayerBox;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD|Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPR_ProgressBar> OtherHPBar;
};
