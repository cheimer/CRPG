// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CRPGModeSelectService.generated.h"

/**
 * 
 */
UCLASS()
class CRPG_API UCRPGModeSelectService : public UBTService
{
	GENERATED_BODY()

public:
	UCRPGModeSelectService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector IsBattleModeKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
