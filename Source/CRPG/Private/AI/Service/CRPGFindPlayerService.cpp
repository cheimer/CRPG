// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/CRPGFindPlayerService.h"
#include "AIController.h"
#include "Components/CRPGAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UCRPGFindPlayerService::UCRPGFindPlayerService()
{
	NodeName = "Find Player";
}

void UCRPGFindPlayerService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Blackboard || !Controller) return;

	const auto PerceptionComp = Controller->FindComponentByClass<UCRPGAIPerceptionComponent>();
	if (!PerceptionComp) return;

	Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComp->GetPlayerActor());

}