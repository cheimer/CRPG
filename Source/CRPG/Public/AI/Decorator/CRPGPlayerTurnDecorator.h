// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CRPGPlayerTurnDecorator.generated.h"

/**
 * 
 */
UCLASS()
class CRPG_API UCRPGPlayerTurnDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UCRPGPlayerTurnDecorator();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
