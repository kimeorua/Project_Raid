// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PR_Enums.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None,
	SwordShield,
	DualSword,
	Lance,
	Katana
};

UENUM(BlueprintType)
enum class EEquipType : uint8
{
	None,
	LeftHand,
	RightHand
};