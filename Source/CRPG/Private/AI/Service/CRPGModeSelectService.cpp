// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/CRPGModeSelectService.h"
#include "CRPGGameModeBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CRPGCoreTypes.h"

UCRPGModeSelectService::UCRPGModeSelectService()
{
	NodeName = "Is Battle Mode";
}

void UCRPGModeSelectService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!GameMode || !Blackboard) return;

	Blackboard->SetValueAsBool(IsBattleModeKey.SelectedKeyName, GameMode->GetScreenMode() == EScreenMode::Battle);
}
