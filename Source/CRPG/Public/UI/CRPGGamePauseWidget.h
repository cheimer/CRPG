// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CRPGBaseWidget.h"
#include "CRPGGamePauseWidget.generated.h"

class UButton;

UCLASS()
class CRPG_API UCRPGGamePauseWidget : public UCRPGBaseWidget
{
	GENERATED_BODY()

public:
	virtual void SetBaseFunc();

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UButton* UnpauseButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MenuButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	FName MenuLevelName = "MenuLevel";

private:
	UFUNCTION()
	void UnPause();

	UFUNCTION()
	void GoMain();
};
