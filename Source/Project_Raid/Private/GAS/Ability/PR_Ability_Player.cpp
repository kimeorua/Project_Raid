// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/PR_Ability_Player.h"

#include "Character/PR_PlayerCharacter.h"

APR_PlayerCharacter* UPR_Ability_Player::GetPR_PlayerCharacter() const
{
	return Cast<APR_PlayerCharacter>(GetPR_BaseCharacter());
}

UActorComponent* UPR_Ability_Player::GetPR_PlayerCharacterComponent(TSubclassOf<UActorComponent> ComponentClass) const
{
	return GetPR_PlayerCharacter() ? GetPR_PlayerCharacter()->FindComponentByClass(ComponentClass) : nullptr;
}
