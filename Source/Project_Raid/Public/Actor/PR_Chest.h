// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/PR_InteractableActor_Base.h"
#include "PR_Chest.generated.h"

class UStaticMeshComponent;

UCLASS()
class PROJECT_RAID_API APR_Chest : public APR_InteractableActor_Base
{
	GENERATED_BODY()
	
public:	
	APR_Chest();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
	void OnChestStateChanged(bool bNewIsOpen);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="StaticMesh", meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> ChestTop;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="StaticMesh", meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> ChestBottom;
};