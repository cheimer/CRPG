// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CRPGBaseWidget.h"
#include "CRPGCoreTypes.h"
#include "CRPGSkillButtonWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class CRPG_API UCRPGSkillButtonWidget : public UCRPGBaseWidget
{
	GENERATED_BODY()

public:
	void SkillSetting();
	void SkillTextSetting();

	FSkillData SkillData;

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UButton* SkillButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SkillText;

	UFUNCTION()
	void SkillClick();

private:
};
