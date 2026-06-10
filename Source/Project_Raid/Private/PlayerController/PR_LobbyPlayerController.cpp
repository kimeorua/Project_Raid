// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/PR_LobbyPlayerController.h"
#include "UI/PR_CharacterSelect_Top.h"

void APR_LobbyPlayerController::RequestOptionPopup(TSubclassOf<UCommonActivatableWidget> OptionClass)
{
	CharacterSelectUI->PushOptionWidget(OptionClass);
}

void APR_LobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsLocalController())
	{
		CharacterSelectUI = Cast<UPR_CharacterSelect_Top>(CreateWidget(this, CharacterSelectClass));
		if (!CharacterSelectUI) { return; }
		
		CharacterSelectUI->AddToViewport();
		
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);
		
		SetInputMode(InputMode);
		SetShowMouseCursor(true);
	}
}
