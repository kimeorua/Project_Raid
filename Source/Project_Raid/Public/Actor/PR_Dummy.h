// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/PR_InteractableActor_Base.h"
#include "PR_Dummy.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;
class USceneComponent;

UCLASS()
class PROJECT_RAID_API APR_Dummy : public APR_InteractableActor_Base
{
	GENERATED_BODY()
	
public:	
	APR_Dummy();
	FTransform GetChestTransform();

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="StaticMesh", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> DummyMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Collision", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCapsuleComponent> DummyCollision;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="StaticMesh", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> ChestOffset;
};
