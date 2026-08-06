// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "PR_InteractableActor_Base.generated.h"

UCLASS()
class PROJECT_RAID_API APR_InteractableActor_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	APR_InteractableActor_Base();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Interaction")
	FGameplayTag RequiredPlayerIndexTag;
	
public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE FGameplayTag GetRequiredPlayerTag() const { return RequiredPlayerIndexTag; }
	FORCEINLINE void SetRequiredPlayerTag(const FGameplayTag& InTag) { RequiredPlayerIndexTag = InTag; }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
