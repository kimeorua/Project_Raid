// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/PR_InputDataAsset.h"

const UInputAction* UPR_InputDataAsset::FindNativeInputActionByTag(const FGameplayTag& InputTag) const
{
    for (const FPR_InputActionConfig& ActionConfig : NativeInputActions)
    {
        if (ActionConfig.InputAction && ActionConfig.InputTag.MatchesTagExact(InputTag))
        {
            return ActionConfig.InputAction;
        }
    }
    return nullptr;
}
