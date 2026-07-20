// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PR_BasicAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS_BASIC(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class APR_GameState_BattleState;

UCLASS()
class PROJECT_RAID_API UPR_BasicAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPR_BasicAttributeSet();
	
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing=OnRep_HP)
	FGameplayAttributeData HP;
	ATTRIBUTE_ACCESSORS_BASIC(UPR_BasicAttributeSet, HP);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing=OnRep_MaxHP)
	FGameplayAttributeData MaxHP;
	ATTRIBUTE_ACCESSORS_BASIC(UPR_BasicAttributeSet, MaxHP);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing=OnRep_SP)
	FGameplayAttributeData SP;
	ATTRIBUTE_ACCESSORS_BASIC(UPR_BasicAttributeSet, SP);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing=OnRep_MaxSP)
	FGameplayAttributeData MaxSP;
	ATTRIBUTE_ACCESSORS_BASIC(UPR_BasicAttributeSet, MaxSP);
	
	UFUNCTION()
	void OnRep_HP(const FGameplayAttributeData& OldVale);
	
	UFUNCTION()
	void OnRep_MaxHP(const FGameplayAttributeData& OldVale);
	
	UFUNCTION()
	void OnRep_SP(const FGameplayAttributeData& OldVale);
	
	UFUNCTION()
	void OnRep_MaxSP(const FGameplayAttributeData& OldVale);
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)override;
	
private:
	UPROPERTY()
	TObjectPtr<APR_GameState_BattleState> PR_GS;
	
private:
	void BroadcastPartyHPChanged();
};
