// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "CRPGAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class CRPG_API UCRPGAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
public:
	AActor* GetPlayerActor() const;
};
