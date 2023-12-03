// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CRPGFindPlayerService.generated.h"

/**
 * 
 */
UCLASS()
class CRPG_API UCRPGFindPlayerService : public UBTService
{
	GENERATED_BODY()

public:
	UCRPGFindPlayerService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
