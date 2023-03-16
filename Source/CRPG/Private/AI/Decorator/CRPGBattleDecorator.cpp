// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/CRPGBattleDecorator.h"
#include "CRPGGameModeBase.h"

UCRPGBattleDecorator::UCRPGBattleDecorator()
{
	NodeName = "Battle Mode";
}

bool UCRPGBattleDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return false;

	return GameMode->GetScreenMode() == EScreenMode::Battle;
}
