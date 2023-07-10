// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CRPGPlayerController.h"
#include "Components/CRPGHealthComponent.h"
#include "Components/CRPGAttackComponent.h"
#include "AI/CRPGAICharacter.h"
#include "CRPGGameModeBase.h"
#include "Kismet/KismetMathLibrary.h"

ACRPGPlayerController::ACRPGPlayerController()
{
<<<<<<< HEAD
}

void ACRPGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = false;
}

=======
	bShowMouseCursor = false;
}


>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
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

<<<<<<< HEAD
		if (AttackComponent && AttackedActor)	
		{
			AttackComponent->Attack(Cast<ACRPGBaseCharacter>(GetPawn()), AttackedActor);
=======
		if (AttackComponent && AttackedActor)
		{
			AttackComponent->Attack(GetPawn(), AttackedActor);
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
		}
	}
}

bool ACRPGPlayerController::IsBattleModeAttack(FHitResult Hit)
{
	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	
<<<<<<< HEAD
	return  GetPawn() && Hit.GetActor() && GameMode->GetScreenMode() == EScreenMode::Battle && 
		GameMode->GetCurrentTurn() == ETurnUser::Player &&
=======
	return  GetPawn() && Hit.GetActor() && GameMode->GetScreenMode() == EScreenMode::Battle && GameMode->GetCurrentTurn() == ETurnUser::Player &&
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
		UKismetMathLibrary::EqualEqual_ObjectObject(GameMode->GetAICharacter(), Hit.GetActor());
}

void ACRPGPlayerController::PauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
	bShowMouseCursor = true;
}
