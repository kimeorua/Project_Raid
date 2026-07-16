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

void UPR_UIComponent_Base::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ASC)
	{
		const UPR_BasicAttributeSet* AttributeSet = Cast<UPR_BasicAttributeSet>(ASC->GetAttributeSet(UPR_BasicAttributeSet::StaticClass()));

		if (AttributeSet)
		{
			if (HPChangedDelegateHandle.IsValid())
			{
				ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHPAttribute()).Remove(HPChangedDelegateHandle);
				HPChangedDelegateHandle.Reset();
			}
			
			if (MaxHPChangedDelegateHandle.IsValid())
			{
				ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHPAttribute()).Remove(MaxHPChangedDelegateHandle);
				MaxHPChangedDelegateHandle.Reset();
			}
		}
	}

	Super::EndPlay(EndPlayReason);
}

void UPR_UIComponent_Base::OnHPChanged(const FOnAttributeChangeData& Data)
{
}

void UPR_UIComponent_Base::OnMaxHPChanged(const FOnAttributeChangeData& Data)
{
}
