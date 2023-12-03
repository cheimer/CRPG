// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../CRPGCoreTypes.h"
#include "UI/CRPGGameHUD.h"
#include "CRPGGameModeBase.generated.h"

class ACRPGBaseCharacter;
class ACRPGAICharacter;
class AAIController;

UCLASS()
class CRPG_API ACRPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACRPGGameModeBase();

	FOnModeChangedSignature OnModeChangedSignature;

	virtual void StartPlay() override;

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	EScreenMode GetScreenMode() { return ScreenMode; }
	void ChangeMode(EScreenMode NewMode);
	ETurnUser GetCurrentTurn() { return CurrentTurn; }
	void SetCurrentTurn(ETurnUser NewTurn) { CurrentTurn = NewTurn; }

	void DeadByAttack(AActor* DamageCauser, AActor* DamagedActor);

	void SetBattleToField();

	void SetPlayerCharacter(AActor* Player);
	void SetAICharacter(AActor* AI);
	
	ACRPGBaseCharacter* GetPlayerCharacter() { return PlayerCharacter; }
	ACRPGBaseCharacter* GetAICharacter() { return AICharacter; }

	void EscapeBattle();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 AINum = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<ACRPGAICharacter> AICharacterClass;

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate);

	virtual bool ClearPause();

private:
	EScreenMode ScreenMode = EScreenMode::Field;
	ETurnUser CurrentTurn = ETurnUser::Player;

	FTimerHandle DeathTimerHandle;
	FTimerHandle EscapeTimerHandle;

	ACRPGBaseCharacter* PlayerCharacter = nullptr;
	ACRPGBaseCharacter* AICharacter = nullptr;

	void SpawnAI();
};
