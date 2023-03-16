// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CRPGBaseWidget.h"
#include "CRPGGameOverWidget.generated.h"

class UButton;

UCLASS()
class CRPG_API UCRPGGameOverWidget : public UCRPGBaseWidget
{
	GENERATED_BODY()

public:
	virtual void SetBaseFunc();

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UButton* GameEndButton;

private:
	UFUNCTION()
	void GameEnd();
};
