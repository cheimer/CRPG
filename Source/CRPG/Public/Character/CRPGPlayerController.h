// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CRPGPlayerController.generated.h"


UCLASS()
class CRPG_API ACRPGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACRPGPlayerController();

protected:
	virtual void SetupInputComponent() override;
<<<<<<< HEAD
	virtual void BeginPlay() override;
=======
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57

private:
	void OnClickScreen();

	void BattleModeAttack(FHitResult Hit);
	bool IsBattleModeAttack(FHitResult Hit);

	void PauseGame();
};
