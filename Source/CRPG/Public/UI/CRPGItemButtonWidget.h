// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CRPGBaseWidget.h"
#include "CRPGCoreTypes.h"
#include "CRPGItemButtonWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class CRPG_API UCRPGItemButtonWidget : public UCRPGBaseWidget
{
	GENERATED_BODY()

public:
	void ItemSetting();
	void ItemTextSetting();

	FItemData ItemData;

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UButton* ItemButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemText;

	UFUNCTION()
	void ItemClick();

private:
};
