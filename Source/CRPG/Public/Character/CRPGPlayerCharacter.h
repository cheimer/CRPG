// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Character/CRPGBaseCharacter.h"
#include "CRPGPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
<<<<<<< HEAD
class UCRPGItemComponent;
=======
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57

UCLASS()
class CRPG_API ACRPGPlayerCharacter : public ACRPGBaseCharacter
{
	GENERATED_BODY()
	
public:
	ACRPGPlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool IsRunning() const override;

	void InFieldMode();

<<<<<<< HEAD
	void UseItem(FText ItemName);

=======
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

<<<<<<< HEAD
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCRPGItemComponent* ItemComponent;

	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, 
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
=======
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, 
		bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57

	virtual void OnDeath() override;

private:
	void MoveUpDown(float amount);
	void MoveLeftRight(float amount);
	void RunStart();
	void RunStop();

	void InBattleMode(AActor* Other);

	float FieldArmLength = 1000.0f;
	FRotator FieldCameraRotator = FRotator(300.0f, 0.0f, 0.0f);

	float BattleArmLength = 200.0f;
	float BattleCameraRotationPitch = 330.0f;
	FVector BattleCameraLocation = FVector(50.0f, 100.0f, 0.0f);

	bool bRunStart = false;
	void AllMovementActivate(bool IsActive);
};
