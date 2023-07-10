// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CRPGAttackComponent.generated.h"

<<<<<<< HEAD
class ACRPGBaseCharacter;

=======
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRPG_API UCRPGAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCRPGAttackComponent();

<<<<<<< HEAD
	void Attack(ACRPGBaseCharacter* DamageCauser, ACRPGBaseCharacter* DamagedActor);

	void TurnEnd();
=======
	float GetBaseDamage() { return BaseDamage; }

	void Attack(AActor* DamageCauser, AActor* DamagedActor);
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57

protected:
	virtual void BeginPlay() override;

<<<<<<< HEAD
private:
	float DamageCalc(ACRPGBaseCharacter* DamageCauser);
=======
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float BaseDamage = 10.0f;

private:
	float DamageCalc();
	void TurnEnd(AActor* DamageCauser);
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
};
