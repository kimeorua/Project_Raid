// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/PR_ComboAttackDataAsset.h"

const FPR_ComboNode* UPR_ComboAttackDataAsset::FindComboNode(const FGameplayTag& InPreviousTag, const FGameplayTag& InInputTag) const
{
	for (const FPR_ComboNode& Node : ComboNodes)
	{
		if (Node.PreviousComboTag.MatchesTag(InPreviousTag) && Node.InputTag.MatchesTag(InInputTag))
		{
			return &Node;
		}
	}
	return nullptr;
}
