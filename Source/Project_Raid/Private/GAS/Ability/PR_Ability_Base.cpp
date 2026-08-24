// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/PR_Ability_Base.h"

#include "Character/PR_BaseCharacter.h"
#include "GAS/ASC/PR_AbilitySystemComponent.h"

UPR_AbilitySystemComponent* UPR_Ability_Base::GetPR_ASC() const
{
	return Cast<UPR_AbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

APR_BaseCharacter* UPR_Ability_Base::GetPR_BaseCharacter() const
{
	return  Cast<APR_BaseCharacter>(CurrentActorInfo->AvatarActor);
}

UActorComponent* UPR_Ability_Base::GetPR_BaseCharacterComponent(TSubclassOf<UActorComponent> ComponentClass) const
{
	return GetPR_BaseCharacter() ? GetPR_BaseCharacter()->FindComponentByClass(ComponentClass) : nullptr;
}