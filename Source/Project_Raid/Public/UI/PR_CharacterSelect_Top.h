// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "PR_CharacterSelect_Top.generated.h"

class UCommonActivatableWidgetStack;
class UPR_CharacterSelect_Sub;
class UCommonActivatableWidget;

UCLASS()
class PROJECT_RAID_API UPR_CharacterSelect_Top : public UCommonUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> CharacterSelectMenuStack;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> OptionStack;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<UPR_CharacterSelect_Sub> CharacterSelectWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UPR_CharacterSelect_Sub> CharacterSelect_SubUI;
	
protected:
	virtual void NativeConstruct() override;
	
public:
	void PushOptionWidget(TSubclassOf<UCommonActivatableWidget> OptionUIClass);
	UPR_CharacterSelect_Sub* GetCharacterSelect_Sub() const;
};
