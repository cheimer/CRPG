// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CRPGAttackComponent.generated.h"

class ACRPGBaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRPG_API UCRPGAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCRPGAttackComponent();

	void Attack(ACRPGBaseCharacter* DamageCauser, ACRPGBaseCharacter* DamagedActor);

	void TurnEnd();

protected:
	virtual void BeginPlay() override;

private:
	float DamageCalc(ACRPGBaseCharacter* DamageCauser);
};
