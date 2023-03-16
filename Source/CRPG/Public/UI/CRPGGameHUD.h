// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CRPGCoreTypes.h"
#include "CRPGGameHUD.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnModeChangedSignature, EScreenMode);

class UCRPGBaseWidget;

UCLASS()
class CRPG_API ACRPGGameHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerFieldWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerBattleWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GamePauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<EScreenMode, UCRPGBaseWidget*> Widgets;

	UPROPERTY()
	UCRPGBaseWidget* CurrentWidget = nullptr;

	void ChangeMode(EScreenMode NewMode);
};
