// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_CreateSessionPopUp.h"
#include "CommonButtonBase.h"
#include "Components/EditableTextBox.h"
#include "GameInstance/PR_GameIntance.h"

void UPR_CreateSessionPopUp::OnCancelButtonClicked()
{
	DeactivateWidget();
}

void UPR_CreateSessionPopUp::OnCreateSessionButtonClicked()
{
	if (UPR_GameIntance* GI = GetGameInstance<UPR_GameIntance>())
	{
		FString RoomName = SessionNameTextBox->GetText().ToString().TrimStartAndEnd();
		GI->CreateSession(RoomName);
		
		DeactivateWidget();
	}
}

void UPR_CreateSessionPopUp::NativeConstruct()
{
	Super::NativeConstruct();
	
	CreateButton->OnClicked().AddUObject(this, &UPR_CreateSessionPopUp::OnCreateSessionButtonClicked);
	CancelButton->OnClicked().AddUObject(this, &UPR_CreateSessionPopUp::OnCancelButtonClicked);
}

UWidget* UPR_CreateSessionPopUp::NativeGetDesiredFocusTarget() const
{
	return CreateButton ? CreateButton : nullptr;
}

void UPR_CreateSessionPopUp::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();
	
	OnCanelButtonCliked.Broadcast();
}