// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_CharacterSelect_Sub.h"

#include "Kismet/KismetSystemLibrary.h"
#include "CommonButtonBase.h"
#include "Components/VerticalBox.h"

#include "GameInstance/PR_GameIntance.h"
#include "Interface/PR_OptionUIInterface.h"
#include "GameState/PR_CharacterSelectGameState.h"
#include "PlayerState/PR_CharacterSelectState.h"
#include "UI/PR_PlayerIfoEntryWidget.h"
#include "PlayerController/PR_LobbyPlayerController.h"

#include "Utils/LogHelper.h"

void UPR_CharacterSelect_Sub::ExitButtonClicked() const
{
	UPR_GameIntance* GameInstance = GetGameInstance<UPR_GameIntance>();
	if (!GameInstance ) { return; }
	UKismetSystemLibrary::QuitGame(GetWorld(), GameInstance->GetFirstLocalPlayerController(), EQuitPreference::Quit, false);
}

void UPR_CharacterSelect_Sub::OptionButtonClicked() const
{
	if (!GameOptionWidgetClass) { return; }
	
	if (IPR_OptionUIInterface* OptionInterface = Cast<IPR_OptionUIInterface>(GetOwningPlayer()))
	{
		OptionInterface->RequestOptionPopup(GameOptionWidgetClass);
	}
}

void UPR_CharacterSelect_Sub::OnReadyButtonClicked()
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;
	
	if (APR_CharacterSelectState* MyPS = PC->GetPlayerState<APR_CharacterSelectState>())
	{
		bool bCurrentReadyState = MyPS->IsReady();
		if (APR_LobbyPlayerController* LobbyPC = Cast<APR_LobbyPlayerController>(PC))
		{
			LobbyPC->RequestChangeIsReady(!bCurrentReadyState);
		}
	}
}

void UPR_CharacterSelect_Sub::InitEntryWidgets()
{
	for (int i = 0; i < 4; i++)
	{
		UPR_PlayerIfoEntryWidget* NewEntry = Cast<UPR_PlayerIfoEntryWidget>(CreateWidget<UUserWidget>(this, EntryWidgetClass));
		if (!NewEntry) { return; }
		
		PlayerInfoList->AddChildToVerticalBox(NewEntry);
		NewEntry->SetVisibility(ESlateVisibility::Collapsed);
		
		ActiveEntryWidgets.Add(NewEntry);
	}
	UpdatePlayerInfoList();
}

void UPR_CharacterSelect_Sub::InitGameStartOrReadyButton()
{
	StartButton->SetIsEnabled(false);
	ReadyButton->SetIsEnabled(false);
	
	if (GetWorld() && GetWorld()->IsNetMode(ENetMode::NM_Client))
	{
		StartButton->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		ReadyButton->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPR_CharacterSelect_Sub::CheckReadyAndStartConditions(APR_CharacterSelectGameState* GameState)
{
	if (!ReadyButton || !StartButton || !GameState) return;

	APlayerController* MyPC = GetOwningPlayer();
	if (!MyPC) return;
	
	bool bAmIHost = (GetWorld() && GetWorld()->GetNetMode() != ENetMode::NM_Client);
	bool bDidISelectWeapon = false;
	bool bAllClientsAreReady = true;
	int32 ClientCount = 0;
	
	for (APlayerState* PS : GameState->PlayerArray)
	{
		if (!PS) continue;
        
		APR_CharacterSelectState* SelectPS = Cast<APR_CharacterSelectState>(PS);
		if (!SelectPS) continue;
		
		if (SelectPS->GetPlayerName().IsEmpty() || SelectPS->GetPlayerName().Equals(TEXT("Player"), ESearchCase::IgnoreCase))
		{
			continue;
		}

		if (SelectPS == MyPC->PlayerState)
		{
			bDidISelectWeapon = (SelectPS->GetCharacterType() != ECharacterType::None);
		}
		else
		{
			ClientCount++;
			if (!SelectPS->IsReady())
			{
				bAllClientsAreReady = false;
			}
		}
	}
	
	if (bAmIHost)
	{
		bool bCanStart = bDidISelectWeapon && (ClientCount == 0 || bAllClientsAreReady);
		StartButton->SetIsEnabled(bCanStart);
	}
	else
	{
		ReadyButton->SetIsEnabled(bDidISelectWeapon);
	}
}

void UPR_CharacterSelect_Sub::NativeConstruct()
{
	Super::NativeConstruct();
	
	ExitButton->OnClicked().AddUObject(this, &UPR_CharacterSelect_Sub::ExitButtonClicked);
	OptionButton->OnClicked().AddUObject(this, &UPR_CharacterSelect_Sub::OptionButtonClicked);
	ReadyButton->OnClicked().AddUObject(this, &UPR_CharacterSelect_Sub::OnReadyButtonClicked);
	
	SetDesiredFocusWidget(NativeGetDesiredFocusTarget());
	
	if (APR_CharacterSelectGameState* GS = Cast<APR_CharacterSelectGameState>(GetWorld()->GetGameState()))
	{
		GS->OnLobbyRefreshRequired.RemoveDynamic(this, &UPR_CharacterSelect_Sub::UpdatePlayerInfoList);
		GS->OnLobbyRefreshRequired.AddDynamic(this, &UPR_CharacterSelect_Sub::UpdatePlayerInfoList);
	}
	
	InitEntryWidgets();
	InitGameStartOrReadyButton();
}

UWidget* UPR_CharacterSelect_Sub::NativeGetDesiredFocusTarget() const
{
	return IsValid(OptionButton) ? OptionButton : Super::NativeGetDesiredFocusTarget();
}

void UPR_CharacterSelect_Sub::UpdatePlayerInfoList()
{
	bool bHasUninitializedPlayer = false;
	
	if (!PlayerInfoList) { return; }

	APR_CharacterSelectGameState* GameState = Cast<APR_CharacterSelectGameState>(GetWorld()->GetGameState());
	if (!GameState) { return; }
	
	TArray<UWidget*> IntendedEntries = PlayerInfoList->GetAllChildren();
	
	for (UWidget* Entry : IntendedEntries)
	{
		Entry->SetVisibility(ESlateVisibility::Collapsed);
	}
	
	int32 CurrentPlayerIndex = 0;
	
	for (APlayerState* PS : GameState->PlayerArray)
	{
		if (!PS) { continue; }
		
		APR_CharacterSelectState* SelectPS = Cast<APR_CharacterSelectState>(PS);
		
		if (!SelectPS) { return; }
		
		if (SelectPS->GetPlayerName().IsEmpty() || SelectPS->GetPlayerName().Equals(TEXT("Player"), ESearchCase::IgnoreCase))
		{
			bHasUninitializedPlayer = true;
			continue;
		}
		
		if (IntendedEntries.IsValidIndex(CurrentPlayerIndex))
		{
			if (UPR_PlayerIfoEntryWidget* TargetEntry = Cast<UPR_PlayerIfoEntryWidget>(IntendedEntries[CurrentPlayerIndex]))
			{
				bool bIsThisStateHost = SelectPS && (CurrentPlayerIndex == 0);
				TargetEntry->InitializeEntryData(SelectPS, bIsThisStateHost);
				TargetEntry->SetVisibility(ESlateVisibility::Visible);
				CurrentPlayerIndex++;
			}
		}
	}
	
	CheckReadyAndStartConditions(GameState);
	
	if (bHasUninitializedPlayer)
	{
		FTimerHandle RetryTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(RetryTimerHandle, this, &UPR_CharacterSelect_Sub::UpdatePlayerInfoList, 0.1f, false);
	}
}

UWidget* UPR_CharacterSelect_Sub::GetReadyOrStartButton()
{
	UWidget* ReturnWidget = nullptr;
	
	if (StartButton->GetIsEnabled())
	{
		ReturnWidget = StartButton;
	}
	else if (OptionButton->GetIsEnabled())
	{
		ReturnWidget = ReadyButton;
	}
	return ReturnWidget;
}

UWidget* UPR_CharacterSelect_Sub::GetOptionButton()
{
	return  OptionButton;
}
