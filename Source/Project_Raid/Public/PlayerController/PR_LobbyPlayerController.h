// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interface/PR_OptionUIInterface.h"
#include "PR_LobbyPlayerController.generated.h"

class UPR_CharacterSelect_Top;
class UCommonActivatableWidget;

UCLASS()
class PROJECT_RAID_API APR_LobbyPlayerController : public APlayerController, public IPR_OptionUIInterface
{
	GENERATED_BODY()
public:
	virtual void RequestOptionPopup(TSubclassOf<UCommonActivatableWidget> OptionClass) override;
protected:
	virtual  void BeginPlay() override;
	
private:
	UPROPERTY()
	TObjectPtr<UPR_CharacterSelect_Top> CharacterSelectUI;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI Class", meta = (AllowPrivateAccess))
	TSubclassOf<UPR_CharacterSelect_Top> CharacterSelectClass;
};
