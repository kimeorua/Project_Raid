// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/UI/PR_UIComponent_Base.h"
#include "AbilitySystemInterface.h"
#include "Character/PR_BaseCharacter.h"

UPR_UIComponent_Base::UPR_UIComponent_Base()
{

}

void UPR_UIComponent_Base::BeginPlay()
{
	Super::BeginPlay();
}

void UPR_UIComponent_Base::InitComponent()
{
	if (!ASC)
	{
		OwnerCharacter = Cast<APR_BaseCharacter>(GetOwner());
		
		if (!OwnerCharacter) { return; }
		
		if (IAbilitySystemInterface* ASInterface = Cast<IAbilitySystemInterface>(OwnerCharacter))
		{
			ASC = ASInterface->GetAbilitySystemComponent();
		}
	}
}