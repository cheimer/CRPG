// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/CRPGAttackTask.h"
#include "Components/CRPGAttackComponent.h"
#include "AIController.h"
#include "Character/CRPGBaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


UCRPGAttackTask::UCRPGAttackTask()
{
	NodeName = "Attack";
}

EBTNodeResult::Type UCRPGAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto TaskOwner = Cast<ACRPGBaseCharacter>(Controller->GetPawn());
	if (!TaskOwner) return EBTNodeResult::Failed;

	const auto AttackComp = TaskOwner->FindComponentByClass<UCRPGAttackComponent>();
	if (!AttackComp) return EBTNodeResult::Failed;

	AActor* DamageCauser = Cast<AActor>(Blackboard->GetValueAsObject(SelfActorKey.SelectedKeyName));
	AActor* DamagedActor = Cast<AActor>(Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName));

	if (DamageCauser && DamagedActor)
	{
		AttackComp->Attack(DamageCauser, DamagedActor);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
