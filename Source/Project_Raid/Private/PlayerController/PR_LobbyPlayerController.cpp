// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/PR_LobbyPlayerController.h"
#include "Framework/Application/SlateApplication.h"
#include "Engine/Engine.h"
#include "GameState/PR_CharacterSelectGameState.h"

#include "UI/PR_CharacterSelect_Top.h"
#include "PlayerState/PR_PlayerState.h"

#include "Utils/LogHelper.h"

void APR_LobbyPlayerController::RequestOptionPopup(TSubclassOf<UCommonActivatableWidget> OptionClass)
{
	CharacterSelectUI->PushOptionWidget(OptionClass);
}

UPR_CharacterSelect_Top* APR_LobbyPlayerController::GetCharacterSelectUI() const
{
	return CharacterSelectUI ? CharacterSelectUI : nullptr;
}

void APR_LobbyPlayerController::RequestChangeCharacter(EWeaponType NewType)
{
	if (APR_PlayerState* PR_PS = GetPlayerState<APR_PlayerState>())
	{
		PR_PS->Server_SetCharacterType(NewType);
	}
}

void APR_LobbyPlayerController::RequestChangeIsReady(bool NewIsReady)
{
	if (APR_PlayerState* PR_PS = GetPlayerState<APR_PlayerState>())
	{
		PR_PS->Server_SetIsReady(NewIsReady);
	}
}

void APR_LobbyPlayerController::Server_RequestStartGame_Implementation()
{
	if (APR_CharacterSelectGameState* GS = Cast<APR_CharacterSelectGameState>(GetWorld()->GetGameState()))
	{
		if (!GameLevel.IsValid())
		{
			GameLevel.LoadSynchronous();
		}
		
		if (!GameLevel) { return; }
		
		const FName LevelName = *FPackageName::ObjectPathToPackageName(GameLevel.ToString());
		GS->StartGame(LevelName.ToString());
	}
}

bool APR_LobbyPlayerController::Server_RequestStartGame_Validate()
{
	return true;
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
