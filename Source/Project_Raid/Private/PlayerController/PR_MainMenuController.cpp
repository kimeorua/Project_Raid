// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/PR_MainMenuController.h"

#include "UI/PR_MainMenu_Top.h"

void APR_MainMenuController::ShowLobbyUI() const
{
	if (!MainMenuUI) { return; }
	MainMenuUI->PopUpLobbyUI();
}

void APR_MainMenuController::RequestOptionPopup(TSubclassOf<UCommonActivatableWidget> OptionClass)
{
	MainMenuUI->PushOptionWidget(OptionClass);
}

void APR_MainMenuController::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsLocalController())
	{
		MainMenuUI = Cast<UPR_MainMenu_Top>(CreateWidget(this, MainMenuUIClass));
		if (!MainMenuUI) { return; }
		
		MainMenuUI->AddToViewport();
		
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);
		
		SetInputMode(InputMode);
		SetShowMouseCursor(true);
	}
}