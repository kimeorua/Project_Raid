// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PR_EnemyCharacter.h"

#include "Component/UI/PR_UIComponent_Enemy.h"

APR_EnemyCharacter::APR_EnemyCharacter()
{
	UIComponent = CreateDefaultSubobject<UPR_UIComponent_Enemy>("Enemy UI Component");
}
