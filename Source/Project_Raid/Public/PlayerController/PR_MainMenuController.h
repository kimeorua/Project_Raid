// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interface/PR_OptionUIInterface.h"
#include "PR_MainMenuController.generated.h"

class UPR_MainMenu_Top;

UCLASS()
class PROJECT_RAID_API APR_MainMenuController : public APlayerController, public IPR_OptionUIInterface
{
	GENERATED_BODY()
public:
	void ShowLobbyUI() const;
	virtual void RequestOptionPopup(TSubclassOf<UCommonActivatableWidget> OptionClass) override;
	FORCEINLINE UPR_MainMenu_Top* GetMasterUI() const { return MainMenuUI; }
	
protected:
	virtual  void BeginPlay() override;
	
private:
	UPROPERTY()
	TObjectPtr<UPR_MainMenu_Top> MainMenuUI;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI Class", meta = (AllowPrivateAccess))
	TSubclassOf<UPR_MainMenu_Top> MainMenuUIClass;
};
