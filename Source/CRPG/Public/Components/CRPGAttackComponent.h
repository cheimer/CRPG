// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CRPGAttackComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRPG_API UCRPGAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCRPGAttackComponent();

	float GetBaseDamage() { return BaseDamage; }

	void Attack(AActor* DamageCauser, AActor* DamagedActor);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float BaseDamage = 10.0f;

private:
	float DamageCalc();
	void TurnEnd(AActor* DamageCauser);
};
