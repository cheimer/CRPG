// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CRPGBaseWidget.h"

void UCRPGBaseWidget::SetBaseFunc()
{

}

void UCRPGBaseWidget::ShowCursor()
{
	if (!GetWorld()) return;

	const auto PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
	}
}

void UCRPGBaseWidget::UnShowCursor()
{
	if (!GetWorld()) return;

	const auto PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;
	}
}