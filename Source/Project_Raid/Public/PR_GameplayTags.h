// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace PR_GameplayTags
{
	//------------------------------Input------------------------------//
	PROJECT_RAID_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PR_Input_Move);
	PROJECT_RAID_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PR_Input_Look);
	PROJECT_RAID_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PR_Input_Attack_Light);
	PROJECT_RAID_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PR_Input_Attack_Heavy);
	
	//------------------------------Data------------------------------//
	PROJECT_RAID_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PR_Data_Rate_HP);
	
	//------------------------------PlayerIndex------------------------------//
	PROJECT_RAID_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Index_1);
	PROJECT_RAID_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Index_2);
	PROJECT_RAID_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Index_3);
	PROJECT_RAID_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Index_4);
	
	//------------------------------Test------------------------------//
	PROJECT_RAID_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PR_Test);
}