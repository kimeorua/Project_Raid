// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "PR_ComboAttackDataAsset.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct FPR_ComboNode
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combo")
	FGameplayTag PreviousComboTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combo")
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combo")
	FGameplayTag NextComboTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combo")
	TObjectPtr<UAnimMontage> ActionMontage;
};

UCLASS()
class PROJECT_RAID_API UPR_ComboAttackDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	const FPR_ComboNode* FindComboNode(const FGameplayTag& InPreviousTag, const FGameplayTag& InInputTag) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combo Data")
	TArray<FPR_ComboNode> ComboNodes;
};
