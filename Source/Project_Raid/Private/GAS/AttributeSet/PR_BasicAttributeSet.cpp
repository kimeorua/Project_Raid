// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeSet/PR_BasicAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"

#include "GameState/PR_GameState_BattelState.h"
#include "Utils/LogHelper.h"

UPR_BasicAttributeSet::UPR_BasicAttributeSet()
{
	InitMaxHP(100.0f);
	InitHP(1.0f);
}

void UPR_BasicAttributeSet::OnRep_HP(const FGameplayAttributeData& OldVale)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPR_BasicAttributeSet, HP, OldVale);
	
	BroadcastPartyHPChanged();
}

void UPR_BasicAttributeSet::OnRep_MaxHP(const FGameplayAttributeData& OldVale)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPR_BasicAttributeSet, MaxHP, OldVale);
}

void UPR_BasicAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UPR_BasicAttributeSet, HP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPR_BasicAttributeSet, MaxHP, COND_None, REPNOTIFY_Always);
}

void UPR_BasicAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetMaxHPAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.0f);
	}
	if (Attribute == GetHPAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHP());
	}
}

void UPR_BasicAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	FGameplayEffectContextHandle Context = Data.EffectSpec.GetEffectContext();
	UAbilitySystemComponent* SourceASC = Context.GetOriginalInstigatorAbilitySystemComponent();
	
	if (!PR_GS)
	{
		PR_GS = GetWorld()->GetGameState<APR_GameState_BattelState>();
	}

	if (Data.EvaluatedData.Attribute == GetHPAttribute())
	{
		SetHP(FMath::Clamp(GetHP(), 0.0f, GetMaxHP()));
		
		BroadcastPartyHPChanged();
	}
}

void UPR_BasicAttributeSet::BroadcastPartyHPChanged()
{
	APawn* Pawn = Cast<APawn>(GetOwningActor());
	if (!Pawn) { return; }
	
	APlayerState* PS = Pawn->GetPlayerState();
	if (!IsValid(PS)) { return; }
	
	if (!IsValid(PR_GS))
	{
		if (UWorld* World = GetWorld())
		{
			PR_GS = World->GetGameState<APR_GameState_BattelState>();
		}
	}
	
	if (IsValid(PR_GS))
	{
		PR_GS->OnPartyHPChanged.Broadcast(PS->GetPlayerId(), GetHP() / GetMaxHP());
	}
}
