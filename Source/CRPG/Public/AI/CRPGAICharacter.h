// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CRPGBaseCharacter.h"
#include "CRPGAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class CRPG_API ACRPGAICharacter : public ACRPGBaseCharacter
{
	GENERATED_BODY()
	
public:
	ACRPGAICharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage")
	float DeathEndTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTree;

protected:
	virtual void OnHealthChange(AActor* DamageCauser, AActor* DamagedActor) override;

	virtual void OnDeath() override;

};
