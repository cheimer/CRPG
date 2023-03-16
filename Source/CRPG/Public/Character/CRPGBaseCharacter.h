// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CRPGBaseCharacter.generated.h"

class UCRPGHealthComponent;
class UCRPGAttackComponent;

UCLASS()
class CRPG_API ACRPGBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACRPGBaseCharacter();

	void PlayAttackAnim();

	void PlayDamagedAnim(USkeletalMeshComponent* MeshComponent);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move", meta = (ClampMin = 100.0, ClampMax = 5000.0))
	float WalkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move", meta = (ClampMin = 100.0, ClampMax = 5000.0))
	float RunSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float LifeSpanTime = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UCRPGHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UCRPGAttackComponent* AttackComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	UAnimMontage* DeathAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	TArray<UAnimMontage*> DamagedAnimArray;

	UFUNCTION()
	virtual void OnDeath();

	UFUNCTION()
	virtual void OnHealthChange(AActor* DamageCauser, AActor* DamagedActor);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetDirection() const;

private:

};
