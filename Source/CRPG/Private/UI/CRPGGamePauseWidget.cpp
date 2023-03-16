// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CRPGGamePauseWidget.h"
#include "Components/Button.h"
#include "CRPGGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UCRPGGamePauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (UnpauseButton)
	{
		UnpauseButton->OnClicked.AddDynamic(this, &UCRPGGamePauseWidget::UnPause);
	}
	
	if (MenuButton)
	{
		MenuButton->OnClicked.AddDynamic(this, &UCRPGGamePauseWidget::GoMain);
	}

}

void UCRPGGamePauseWidget::SetBaseFunc()
{
	ShowCursor();

	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());

	if (GameMode)
	{
		if (GameMode->GetScreenMode() == EScreenMode::Battle)
		{
			ShowCursor();
		}
		else if (GameMode->GetScreenMode() == EScreenMode::Field)
		{
			UnShowCursor();
		}
	}
}

void UCRPGGamePauseWidget::UnPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();

}

void UCRPGGamePauseWidget::GoMain()
{
	if (MenuLevelName != "")
	{
		UGameplayStatics::OpenLevel(this, MenuLevelName);
	}

}
