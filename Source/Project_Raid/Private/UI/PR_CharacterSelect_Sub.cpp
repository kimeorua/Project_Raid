// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_CharacterSelect_Sub.h"

#include "Kismet/KismetSystemLibrary.h"
#include "CommonButtonBase.h"
#include "CommonListView.h"

#include "GameInstance/PR_GameIntance.h"
#include "Interface/PR_OptionUIInterface.h"
#include "ListRow/PR_PlayerInfoDataRow.h"
#include "GameState/PR_CharacterSelectGameState.h"
#include "PlayerState/PR_CharacterSelectState.h"

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

void UPR_CharacterSelect_Sub::NativeConstruct()
{
	Super::NativeConstruct();
	
	ExitButton->OnClicked().AddUObject(this, &UPR_CharacterSelect_Sub::ExitButtonClicked);
	OptionButton->OnClicked().AddUObject(this, &UPR_CharacterSelect_Sub::OptionButtonClicked);
	
	SetDesiredFocusWidget(NativeGetDesiredFocusTarget());
	
	if (APR_CharacterSelectGameState* GS = Cast<APR_CharacterSelectGameState>(GetWorld()->GetGameState()))
	{
		GS->OnLobbyRefreshRequired.RemoveDynamic(this, &UPR_CharacterSelect_Sub::UpdatePlayerInfoList);
		GS->OnLobbyRefreshRequired.AddDynamic(this, &UPR_CharacterSelect_Sub::UpdatePlayerInfoList);
	}
	
	UpdatePlayerInfoList();
}

UWidget* UPR_CharacterSelect_Sub::NativeGetDesiredFocusTarget() const
{
	return IsValid(OptionButton) ? OptionButton : Super::NativeGetDesiredFocusTarget();
}

void UPR_CharacterSelect_Sub::UpdatePlayerInfoList()
{
	bool bHasUninitializedPlayer = false;
	
	if (!PlayerInfoListView) { return; }

	APR_CharacterSelectGameState* GameState = Cast<APR_CharacterSelectGameState>(GetWorld()->GetGameState());
	if (!GameState) { return; }
	
	TArray<UObject*> NewItems;

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

		UPR_PlayerInfoDataRow* NewRow = NewObject<UPR_PlayerInfoDataRow>(this, UPR_PlayerInfoDataRow::StaticClass());
		if (NewRow)
		{
			NewRow->PlayerName = PS->GetPlayerName();
			NewRow->SelectCharacterType = SelectPS->GetCharacterType();
			NewRow->OwningPlayerState = SelectPS;
			NewItems.Add(NewRow);
		}
	}
	if (NewItems.Num() > 0)
	{
		PlayerInfoListView->ClearListItems();
		for (UObject* Item : NewItems)
		{
			PlayerInfoListView->AddItem(Item);
		}
	}
	if (bHasUninitializedPlayer)
	{
		FTimerHandle RetryTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(RetryTimerHandle, this, &UPR_CharacterSelect_Sub::UpdatePlayerInfoList, 0.1f, false);
	}
}
