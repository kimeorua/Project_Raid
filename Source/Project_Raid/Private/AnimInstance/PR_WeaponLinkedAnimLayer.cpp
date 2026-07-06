// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/PR_WeaponLinkedAnimLayer.h"

#include "AnimInstance/PR_AnimInstance_Player.h"

UPR_AnimInstance_Player* UPR_WeaponLinkedAnimLayer::GetPlayerAnimInstance() const
{
	return Cast<UPR_AnimInstance_Player>( GetOwningComponent()->GetAnimInstance());
}
