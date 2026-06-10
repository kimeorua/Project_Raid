// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_CharacterSelect_Sub.h"

#include "Kismet/KismetSystemLibrary.h"
#include "CommonButtonBase.h"

#include "GameInstance/PR_GameIntance.h"
#include "Interface/PR_OptionUIInterface.h"

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
}
