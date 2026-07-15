// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PR_ProgressBar.generated.h"

class UTextBlock;
class UProgressBar;

UCLASS()
class PROJECT_RAID_API UPR_ProgressBar : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> Bar;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> Text;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess="true"))
	FLinearColor Color = FLinearColor::Red;
	
	virtual void NativeConstruct() override;
	
public:
	void SetPercent(float Percent) const;
};
