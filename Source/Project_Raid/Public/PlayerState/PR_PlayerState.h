// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Type/Enums/PR_Enums.h"
#include "PR_PlayerState.generated.h"

UCLASS()
class PROJECT_RAID_API APR_PlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	APR_PlayerState();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(Server, Reliable)
	void Server_SetCharacterType(EWeaponType NewType);
	
	FORCEINLINE EWeaponType GetWeaponType() const { return SelectedWeapon;}
	
	UFUNCTION(Server, Reliable)
	void Server_SetIsReady(bool bNewReadyState);
	
	FORCEINLINE bool IsReady() const { return bIsReady;}

protected:
	virtual void CopyProperties(APlayerState* PlayerState)override;
	
private:
	UPROPERTY(ReplicatedUsing = OnRep_CharacterType)
	EWeaponType SelectedWeapon;
	
	UPROPERTY(ReplicatedUsing = OnRep_IsReady)
	bool bIsReady = false;
	
	UFUNCTION() 
	void OnRep_CharacterType();
	
	UFUNCTION() 
	void OnRep_IsReady();
};
