// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
<<<<<<< HEAD
#include "CRPGCoreTypes.h"
=======
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
#include "CRPGBaseCharacter.generated.h"

class UCRPGHealthComponent;
class UCRPGAttackComponent;
<<<<<<< HEAD
class UUserWidget;
=======
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57

UCLASS()
class CRPG_API ACRPGBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACRPGBaseCharacter();

<<<<<<< HEAD
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetDirection() const;

=======
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
	void PlayAttackAnim();

	void PlayDamagedAnim(USkeletalMeshComponent* MeshComponent);

<<<<<<< HEAD
	FSkillData GetSkill(int32 Idx) { return Skills[Idx]; }
	void ChangeCurrentSkill(int32 idx);
	bool UseSkill();

	int32 GetCurrentSkillIndex() { return CurrentSkillIndex; }
	void CurrentSkillIndexReset() { CurrentSkillIndex = 0; }
	void CurrentSkillIndexAdd() { CurrentSkillIndex++; }
	int32 SkillNum;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void StatusStringSet(FString str) { StatusString = str; }

	UFUNCTION(BlueprintCallable, Category = "UI")
	FString StatusStringGet() { return StatusString; }

=======
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move", meta = (ClampMin = 100.0, ClampMax = 5000.0))
	float WalkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move", meta = (ClampMin = 100.0, ClampMax = 5000.0))
	float RunSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float LifeSpanTime = 5.0f;

<<<<<<< HEAD
	int32 CurrentSkillIndex = 0;

=======
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
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

<<<<<<< HEAD
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill", meta = (ClampMin = 0.0, ClampMax = 4.0))
	TArray<FSkillData> Skills;

=======
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
	UFUNCTION()
	virtual void OnDeath();

	UFUNCTION()
	virtual void OnHealthChange(AActor* DamageCauser, AActor* DamagedActor);

<<<<<<< HEAD
private:
	bool CanUseSkill(int Index);

	FString StatusString;
=======
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetDirection() const;

private:

>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
};
