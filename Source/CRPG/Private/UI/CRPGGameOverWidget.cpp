// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CRPGGameOverWidget.h"
#include "Components/Button.h"
#include "CRPGGameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"

void UCRPGGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GameEndButton)
	{
		GameEndButton->OnClicked.AddDynamic(this, &UCRPGGameOverWidget::GameEnd);
	}

}

void UCRPGGameOverWidget::SetBaseFunc()
{
	ShowCursor();
}

void UCRPGGameOverWidget::GameEnd()
{
	if (!GetWorld() || !GetOwningPlayer()) return;

	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
