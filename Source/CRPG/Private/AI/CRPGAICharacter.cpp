// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CRPGAICharacter.h"
#include "Components/CRPGHealthComponent.h"
#include "CRPGGameModeBase.h"
#include "AI/CRPGAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BrainComponent.h"

ACRPGAICharacter::ACRPGAICharacter()
{
	//AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ACRPGAIController::StaticClass();


	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->RotationRate.Yaw = 270.0f;

}

void ACRPGAICharacter::OnHealthChange(AActor* DamageCauser, AActor* DamagedActor)
{
	if (!GetWorld()) return;

	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	if (FindComponentByClass<UCRPGHealthComponent>() && FindComponentByClass<UCRPGHealthComponent>()->IsDead())
	{
		GameMode->DeadByAttack(DamageCauser, DamagedActor);

		OnDeath();	
	}

}

void ACRPGAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto AIController = Cast<ACRPGAIController>(GetController());
	const auto BrainComp = AIController->FindComponentByClass<UBrainComponent>();

	BrainComp->StopLogic("Dead");

}