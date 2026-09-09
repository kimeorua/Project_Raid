// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Ability/PR_ComboAttackAbility_Player.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

#include "DeveloperSetting/PR_ComboAttackDeveloperSetting.h"
#include "PR_GameplayTags.h"

UPR_ComboAttackAbility_Player::UPR_ComboAttackAbility_Player()
{
    CurrentComboTag = FGameplayTag::EmptyTag;
    BufferedInputTag = FGameplayTag::EmptyTag;
    bIsComboWindowOpen = false;
    
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UPR_ComboAttackAbility_Player::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    
    UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
    if (!ASC)
    {
       EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
       return;
    }
    
    if (ASC->GetOwnerRole() == ROLE_Authority)
    {
       ASC->AbilityTargetDataSetDelegate(Handle, ActivationInfo.GetActivationPredictionKey())
          .AddUObject(this, &UPR_ComboAttackAbility_Player::OnTargetDataReceived);
    }
    
    WeaponDataAsset = UPR_ComboAttackDeveloperSetting::GetWeaponDataAsset(WeaponType);
    if (!WeaponDataAsset)
    {
       EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
       return;
    }
    
    CurrentComboTag = FGameplayTag::EmptyTag;
    BufferedInputTag = FGameplayTag::EmptyTag;
    
    FGameplayTag InitialInputTag = GetBoundInputTag();
    const FPR_ComboNode* FirstNode = WeaponDataAsset->FindComboNode(CurrentComboTag, InitialInputTag);
       
    if (FirstNode)
    {
       ExecuteComboNode(*FirstNode);
    }
    else
    {
       EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
    }
}

void UPR_ComboAttackAbility_Player::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo)
{
    Super::InputPressed(Handle, ActorInfo, ActivationInfo);

    FGameplayTag InputTag = GetBoundInputTag();
    if (InputTag.IsValid())
    {
        SendInputTagToServer(InputTag);
    }
}

void UPR_ComboAttackAbility_Player::SendInputTagToServer(FGameplayTag InputTag)
{
    UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
    if (!ASC) return;
    
    if (IsLocallyControlled())
    {
        FGameplayAbilityTargetDataHandle TargetDataHandle;
        FGameplayAbilityTargetData_SingleTargetHit* NewData = new FGameplayAbilityTargetData_SingleTargetHit();
        
        TargetDataHandle.Add(NewData);
        
        HandleInputTagReceived(InputTag);
        
        ASC->CallServerSetReplicatedTargetData(
            CurrentSpecHandle,
            CurrentActivationInfo.GetActivationPredictionKey(),
            TargetDataHandle,
            InputTag,
            ASC->ScopedPredictionKey
        );
    }
    else if (ASC->GetOwnerRole() == ROLE_Authority)
    {
        HandleInputTagReceived(InputTag);
    }
}

void UPR_ComboAttackAbility_Player::OnTargetDataReceived(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ApplicationTag)
{
    UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
    if (ASC)
    {
        ASC->ConsumeClientReplicatedTargetData(CurrentSpecHandle, CurrentActivationInfo.GetActivationPredictionKey());
    }
    
    HandleInputTagReceived(ApplicationTag);
}

void UPR_ComboAttackAbility_Player::HandleInputTagReceived(FGameplayTag InputTag)
{
    if (!InputTag.IsValid()) return;

    BufferedInputTag = InputTag;
}

void UPR_ComboAttackAbility_Player::ExecuteComboNode(const FPR_ComboNode& Node)
{
    ClearAllComboTasks();

    CurrentComboTag = Node.NextComboTag;
    
    BufferedInputTag = FGameplayTag::EmptyTag;
    bIsComboWindowOpen = false;
    
    ActiveMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
       this, NAME_None, Node.ActionMontage, 1.0f, NAME_None, false
    );

    if (ActiveMontageTask)
    {
        ActiveMontageTask->OnCompleted.AddDynamic(this, &UPR_ComboAttackAbility_Player::OnMontageEnded);
        ActiveMontageTask->OnInterrupted.AddDynamic(this, &UPR_ComboAttackAbility_Player::OnMontageEnded);
        ActiveMontageTask->OnCancelled.AddDynamic(this, &UPR_ComboAttackAbility_Player::OnMontageEnded);
        ActiveMontageTask->ReadyForActivation();
        
        // ANS의 ComboWindow Open 이벤트 대기 Task
        ActiveWaitOpenTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
           this, PR_GameplayTags::PlayerState_Combat_ComboWindow, nullptr, false, false
        );
        ActiveWaitOpenTask->EventReceived.AddDynamic(this, &UPR_ComboAttackAbility_Player::OnComboWindowOpened);
        ActiveWaitOpenTask->ReadyForActivation();
    }
    else
    {
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
    }
}

void UPR_ComboAttackAbility_Player::OnComboWindowOpened(FGameplayEventData Payload)
{
    bIsComboWindowOpen = true;
    
    if (BufferedInputTag.IsValid() && WeaponDataAsset)
    {
        FGameplayTag PendingInputTag = BufferedInputTag;
        
        BufferedInputTag = FGameplayTag::EmptyTag;
        bIsComboWindowOpen = false;

        const FPR_ComboNode* NextNode = WeaponDataAsset->FindComboNode(CurrentComboTag, PendingInputTag);
        if (NextNode)
        {
            ExecuteComboNode(*NextNode);
            return;
        }
    }
    
    ActiveWaitCloseTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
       this, PR_GameplayTags::PlayerState_Combat_ComboWindow_Close, nullptr, false, false
    );
    ActiveWaitCloseTask->EventReceived.AddDynamic(this, &UPR_ComboAttackAbility_Player::OnComboWindowClosed);
    ActiveWaitCloseTask->ReadyForActivation();
}

void UPR_ComboAttackAbility_Player::OnComboWindowClosed(FGameplayEventData Payload)
{
    bIsComboWindowOpen = false;
}

void UPR_ComboAttackAbility_Player::OnMontageEnded()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UPR_ComboAttackAbility_Player::ClearAllComboTasks()
{
    if (ActiveMontageTask)
    {
        ActiveMontageTask->OnCompleted.RemoveAll(this);
        ActiveMontageTask->OnInterrupted.RemoveAll(this);
        ActiveMontageTask->OnCancelled.RemoveAll(this);
        ActiveMontageTask->EndTask();
        ActiveMontageTask = nullptr;
    }

    if (ActiveWaitOpenTask)
    {
        ActiveWaitOpenTask->EventReceived.RemoveAll(this);
        ActiveWaitOpenTask->EndTask();
        ActiveWaitOpenTask = nullptr;
    }

    if (ActiveWaitCloseTask)
    {
        ActiveWaitCloseTask->EventReceived.RemoveAll(this);
        ActiveWaitCloseTask->EndTask();
        ActiveWaitCloseTask = nullptr;
    }
}

void UPR_ComboAttackAbility_Player::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
    if (ASC && ASC->GetOwnerRole() == ROLE_Authority)
    {
        ASC->AbilityTargetDataSetDelegate(Handle, ActivationInfo.GetActivationPredictionKey()).RemoveAll(this);
    }

    ClearAllComboTasks();
    
    CurrentComboTag = FGameplayTag::EmptyTag;
    BufferedInputTag = FGameplayTag::EmptyTag;
    bIsComboWindowOpen = false;
    
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

FGameplayTag UPR_ComboAttackAbility_Player::GetBoundInputTag() const
{
    if (const FGameplayAbilitySpec* Spec = GetCurrentAbilitySpec())
    {
       for (const FGameplayTag& Tag : Spec->GetDynamicSpecSourceTags())
       {
          if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("PR"))))
          {
             return Tag;
          }
       }
    }
    return FGameplayTag::EmptyTag;
}