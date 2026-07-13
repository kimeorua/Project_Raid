// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUD/PR_ProgressBar.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPR_ProgressBar::NativeConstruct()
{
	Super::NativeConstruct();
	Bar->SetFillColorAndOpacity(Color);
}

void UPR_ProgressBar::SetPercent(float Percent)
{

}
