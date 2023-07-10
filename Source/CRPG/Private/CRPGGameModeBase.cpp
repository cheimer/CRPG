// Copyright Epic Games, Inc. All Rights Reserved.


#include "CRPGGameModeBase.h"
#include "Character/CRPGBaseCharacter.h"
#include "Character/CRPGPlayerCharacter.h"
#include "Character/CRPGPlayerController.h"
#include "AI/CRPGAICharacter.h"
#include "AI/CRPGAIController.h"
#include "UI/CRPGGameHUD.h"
#include "CRPGCoreTypes.h"

ACRPGGameModeBase::ACRPGGameModeBase()
{
	DefaultPawnClass = ACRPGBaseCharacter::StaticClass();
	PlayerControllerClass = ACRPGPlayerController::StaticClass();
	HUDClass = ACRPGGameHUD::StaticClass();
}

void ACRPGGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnAI();
}

UClass* ACRPGGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AICharacterClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ACRPGGameModeBase::SpawnAI()
{
	if (!GetWorld()) return;

	for (int32 i = 0; i < AINum; i++)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto CRPGAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(CRPGAIController);
	}
}

void ACRPGGameModeBase::DeadByAttack(AActor* DamageCauser, AActor* DamagedActor)
{
	if (const auto DamagedAI = Cast<ACRPGAICharacter>(DamagedActor))
	{
		GetWorld()->GetTimerManager().SetTimer(DeathTimerHandle, this, &ACRPGGameModeBase::SetBattleToField, DamagedAI->DeathEndTime, false);
	}
}

void ACRPGGameModeBase::EscapeBattle()
{
	GetWorld()->GetTimerManager().SetTimer(EscapeTimerHandle, this, &ACRPGGameModeBase::SetBattleToField, 3.0f, false);
	
	if (!PlayerCharacter || !PlayerCharacter->GetController()) return;
	
	const auto PlayerController = PlayerCharacter->GetController<APlayerController>();

}

void ACRPGGameModeBase::SetBattleToField()
{
	const auto Controller = Cast<ACRPGPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!Controller) return;

	const auto Player = Cast<ACRPGPlayerCharacter>(Controller->GetPawn());
	if (!Player) return;

	Player->InFieldMode();
}

void ACRPGGameModeBase::SetPlayerCharacter(AActor* Player)
{
	const auto PlayerCast = Cast<ACRPGPlayerCharacter>(Player);
	if (!PlayerCast) return;
	PlayerCharacter = PlayerCast;
}

void ACRPGGameModeBase::SetAICharacter(AActor* AI)
{
	const auto AICast = Cast<ACRPGAICharacter>(AI);
	if (!AICast) return;
	AICharacter = AICast;
}

void ACRPGGameModeBase::ChangeMode(EScreenMode NewMode)
{
	if (ScreenMode == NewMode) return;

	ScreenMode = NewMode;
	OnModeChangedSignature.Broadcast(ScreenMode);

}

bool ACRPGGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	bool IsPause = Super::SetPause(PC, CanUnpauseDelegate);

	if (IsPause)
	{
		OnModeChangedSignature.Broadcast(EScreenMode::GamePause);
	}

	return IsPause;
}

bool ACRPGGameModeBase::ClearPause()
{
	bool IsPause = Super::ClearPause();

	if (IsPause)
	{
		OnModeChangedSignature.Broadcast(ScreenMode);
	}

	return IsPause;
}