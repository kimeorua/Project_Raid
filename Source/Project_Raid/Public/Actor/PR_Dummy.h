// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PR_Dummy.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;

UCLASS()
class PROJECT_RAID_API APR_Dummy : public AActor
{
	GENERATED_BODY()
	
public:	
	APR_Dummy();

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="StaticMesh", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> DummyMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Collision", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCapsuleComponent> DummyCollision;
};
