// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CRPGBaseWidget.h"
#include "CRPGTextBoxWidget.generated.h"

class UEditableTextBox;

UCLASS()
class CRPG_API UCRPGTextBoxWidget : public UCRPGBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* TextBox;

	UFUNCTION(BlueprintCallable, Category = "UI")
	FString GetPlayerStatusString() const;

};
