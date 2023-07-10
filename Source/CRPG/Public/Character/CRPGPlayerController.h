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
	virtual void BeginPlay() override;

private:
	void OnClickScreen();

	void BattleModeAttack(FHitResult Hit);
	bool IsBattleModeAttack(FHitResult Hit);

	void PauseGame();
};
