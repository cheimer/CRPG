// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/CRPGPlayerTurnDecorator.h"
#include "CRPGGameModeBase.h"
#include "CRPGCoreTypes.h"

UCRPGPlayerTurnDecorator::UCRPGPlayerTurnDecorator()
{
	NodeName = "Player Turn";
}

bool UCRPGPlayerTurnDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return false;

	return GameMode->GetCurrentTurn() == ETurnUser::Player;
}
