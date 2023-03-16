// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CRPGGameHUD.h"
#include "CRPGCoreTypes.h"
#include "UI/CRPGBaseWidget.h"
#include "CRPGGameModeBase.h"

void ACRPGGameHUD::BeginPlay()
{
	Super::BeginPlay();

	Widgets.Add(EScreenMode::Battle, CreateWidget<UCRPGBaseWidget>(GetWorld(), PlayerBattleWidgetClass));
	Widgets.Add(EScreenMode::Field, CreateWidget<UCRPGBaseWidget>(GetWorld(), PlayerFieldWidgetClass));
	Widgets.Add(EScreenMode::GamePause, CreateWidget<UCRPGBaseWidget>(GetWorld(), GamePauseWidgetClass));
	Widgets.Add(EScreenMode::GameOver, CreateWidget<UCRPGBaseWidget>(GetWorld(), GameOverWidgetClass));

	for (auto WidgetPair : Widgets)
	{
		const auto WidgetMode = WidgetPair.Value;
		if (!WidgetMode) continue;

		WidgetMode->AddToViewport();
		WidgetMode->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GetWorld())
	{
		const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnModeChangedSignature.AddUObject(this, &ACRPGGameHUD::ChangeMode);
		}
	}
	ChangeMode(EScreenMode::Field);
}

void ACRPGGameHUD::ChangeMode(EScreenMode NewMode)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if (Widgets.Contains(NewMode))
	{
		CurrentWidget = Widgets[NewMode];
	}
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
		CurrentWidget->SetBaseFunc();
	}

}
