// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CRPGPlayerController.h"
#include "Components/CRPGHealthComponent.h"
#include "Components/CRPGAttackComponent.h"
#include "AI/CRPGAICharacter.h"
#include "CRPGGameModeBase.h"
#include "Kismet/KismetMathLibrary.h"

ACRPGPlayerController::ACRPGPlayerController()
{
}

void ACRPGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = false;
}

void ACRPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Click", IE_Pressed, this, &ACRPGPlayerController::OnClickScreen);
	InputComponent->BindAction("Pause", IE_Pressed, this, &ACRPGPlayerController::PauseGame);
}

void ACRPGPlayerController::OnClickScreen()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Pawn, false, Hit);

	BattleModeAttack(Hit);
}

void ACRPGPlayerController::BattleModeAttack(FHitResult Hit)
{
	if (IsBattleModeAttack(Hit))
	{
		const auto AttackComponent = GetPawn()->FindComponentByClass<UCRPGAttackComponent>();
		ACRPGAICharacter* AttackedActor = Cast<ACRPGAICharacter>(Hit.GetActor());

		if (AttackComponent && AttackedActor)	
		{
			AttackComponent->Attack(Cast<ACRPGBaseCharacter>(GetPawn()), AttackedActor);
		}
	}
}

bool ACRPGPlayerController::IsBattleModeAttack(FHitResult Hit)
{
	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	
	return  GetPawn() && Hit.GetActor() && GameMode->GetScreenMode() == EScreenMode::Battle && 
		GameMode->GetCurrentTurn() == ETurnUser::Player &&
		UKismetMathLibrary::EqualEqual_ObjectObject(GameMode->GetAICharacter(), Hit.GetActor());
}

void ACRPGPlayerController::PauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
	bShowMouseCursor = true;
}
