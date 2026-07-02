// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Type/Enums/PR_Enums.h"
#include "PR_Weapon_Base.generated.h"

class UStaticMeshComponent;

UCLASS()
class PROJECT_RAID_API APR_Weapon_Base : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> WeaponMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = true))
	EEquipType EquipType = EEquipType::LeftHand;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = true))
	FName AttachSocket;
	
protected:
	virtual void BeginPlay() override;
	
public:	
	APR_Weapon_Base();
	
	FORCEINLINE EEquipType GetEquipType() const { return EquipType; }
	FORCEINLINE FName GetAttachSocket() const { return AttachSocket; }
};
