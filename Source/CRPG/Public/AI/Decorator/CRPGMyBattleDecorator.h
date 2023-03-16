// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CRPGMyBattleDecorator.generated.h"

/**
 * 
 */
UCLASS()
class CRPG_API UCRPGMyBattleDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UCRPGMyBattleDecorator();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
