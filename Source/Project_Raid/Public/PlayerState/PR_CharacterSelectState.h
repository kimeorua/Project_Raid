// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Type/Enums/PR_Enums.h"
#include "PR_CharacterSelectState.generated.h"

UCLASS()
class PROJECT_RAID_API APR_CharacterSelectState : public APlayerState
{
	GENERATED_BODY()
public:
	APR_CharacterSelectState();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(Server, Reliable)
	void Server_SetCharacterType(ECharacterType NewType);
	
	FORCEINLINE ECharacterType GetCharacterType() const { return SelectedCharacter;}

private:
	UPROPERTY(ReplicatedUsing = OnRep_CharacterType)
	ECharacterType SelectedCharacter;
	
	UFUNCTION() 
	void OnRep_CharacterType();
};
