// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CRPGMenuWidget.generated.h"

class UButton;

UCLASS()
class CRPG_API UCRPGMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	FName StartLevelName = "TestMap";

private:
	UFUNCTION()
	void StartClick();

};
