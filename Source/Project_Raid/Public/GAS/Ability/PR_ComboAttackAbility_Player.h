// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/PR_ComboAttackDataAsset.h"
#include "GAS/Ability/PR_Ability_Player.h"
#include "Type/Enums/PR_Enums.h"
#include "PR_ComboAttackAbility_Player.generated.h"

class UAnimMontage;
class UPR_ComboAttackDataAsset;
class UAbilityTask_PlayMontageAndWait;
class UAbilityTask_WaitGameplayEvent;

UCLASS()
class PROJECT_RAID_API UPR_ComboAttackAbility_Player : public UPR_Ability_Player
{
    GENERATED_BODY()
    
public:
    UPR_ComboAttackAbility_Player();
    virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

protected:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
    
    void ExecuteComboNode(const FPR_ComboNode& Node);
    void SendInputTagToServer(FGameplayTag InputTag);
    void HandleInputTagReceived(FGameplayTag InputTag);
    
    void OnTargetDataReceived(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ApplicationTag);
    
    UFUNCTION()
    void OnComboWindowOpened(FGameplayEventData Payload);
    
    UFUNCTION()
    void OnComboWindowClosed(FGameplayEventData Payload);
    
    UFUNCTION()
    void OnMontageEnded();
    
    FGameplayTag GetBoundInputTag() const;
    void ClearAllComboTasks();

protected:
    UPROPERTY()
    TObjectPtr<UAbilityTask_PlayMontageAndWait> ActiveMontageTask;

    UPROPERTY()
    TObjectPtr<UAbilityTask_WaitGameplayEvent> ActiveWaitOpenTask;

    UPROPERTY()
    TObjectPtr<UAbilityTask_WaitGameplayEvent> ActiveWaitCloseTask;

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combo|Setup", meta=(AllowPrivateAccess = true))
    EWeaponType WeaponType = EWeaponType::None;
    
    UPROPERTY(BlueprintReadOnly, Category = "Combo|State", meta=(AllowPrivateAccess = true))
    FGameplayTag CurrentComboTag;
    
    UPROPERTY(BlueprintReadOnly, Category = "Combo|State", meta=(AllowPrivateAccess = true))
    FGameplayTag BufferedInputTag;
    
    UPROPERTY(BlueprintReadOnly, Category = "Combo|State", meta=(AllowPrivateAccess = true))
    bool bIsComboWindowOpen = false;
    
    UPROPERTY()
    TObjectPtr<const UPR_ComboAttackDataAsset> WeaponDataAsset;
};