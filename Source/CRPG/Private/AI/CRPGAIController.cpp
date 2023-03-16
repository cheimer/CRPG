// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CRPGAIController.h"
#include "AI/CRPGAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CRPGAIPerceptionComponent.h"

ACRPGAIController::ACRPGAIController()
{
	CRPGAIPerceptionComponent = CreateDefaultSubobject<UCRPGAIPerceptionComponent>("CRPGAIPerceptionComponent");
	SetPerceptionComponent(*CRPGAIPerceptionComponent);
}

void ACRPGAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetFocus(GetFocusOnActor());

}

void ACRPGAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (const auto AICharacter = Cast<ACRPGAICharacter>(InPawn))
	{
		RunBehaviorTree(AICharacter->BehaviorTree);
	}
}

AActor* ACRPGAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;

	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}