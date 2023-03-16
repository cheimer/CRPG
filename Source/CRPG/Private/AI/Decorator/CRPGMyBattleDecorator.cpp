// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/CRPGMyBattleDecorator.h"
#include "CRPGGameModeBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController.h"
#include "Character/CRPGBaseCharacter.h"

UCRPGMyBattleDecorator::UCRPGMyBattleDecorator()
{
	NodeName = "My Battle Mode";
}

bool UCRPGMyBattleDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return false;

	bool BattleIn = UKismetMathLibrary::EqualEqual_ObjectObject(OwnerComp.GetAIOwner()->GetPawn(), GameMode->GetAICharacter());

	return GameMode->GetScreenMode() == EScreenMode::Battle && BattleIn;
}
