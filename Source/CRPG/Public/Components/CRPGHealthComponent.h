// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CRPGHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangeSignature, AActor*, AActor*)

class UCameraShakeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRPG_API UCRPGHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	FOnDeathSignature OnDeathSignature;
	FOnHealthChangeSignature OnHealthChangeSignature;

	UCRPGHealthComponent();

	float GetHealth() { return Health; }
	float GetHealthPercent() { return Health / MaxHealth; }

	bool IsDead() const { return FMath::IsNearlyZero(Health); }

	bool IsMaxHP();
	void HealHP(float HealAmount);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UCameraShakeBase> CameraShake;

private:
	float Health = 0.0f;

	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, 
		class AController* InstigatedBy, AActor* DamageCauser);

	void SetHealth(float NewHealth);
	
	void PlayCameraShake();

};
