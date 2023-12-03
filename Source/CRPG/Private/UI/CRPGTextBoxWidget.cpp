// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CRPGTextBoxWidget.h"
#include "Components/EditableTextBox.h"
#include "CRPGGameModeBase.h"
#include "Character/CRPGBaseCharacter.h"

FString UCRPGTextBoxWidget::GetPlayerStatusString() const
{
	if (!GetWorld()) return "";

	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return "";

	const auto Player = GameMode->GetPlayerCharacter();
	if (!Player) return "";

	return Player->StatusStringGet();
}
