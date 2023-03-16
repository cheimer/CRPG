// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CRPGAttackComponent.h"
#include "Components/CRPGHealthComponent.h"
#include "Character/CRPGBaseCharacter.h"
#include "DamageType/CRPGSmallBite.h"
#include "CRPGGameModeBase.h"
#include "CRPGCoreTypes.h"

UCRPGAttackComponent::UCRPGAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UCRPGAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UCRPGAttackComponent::Attack(AActor* DamageCauser, AActor* DamagedActor)
{
	const auto Owner = Cast<ACRPGBaseCharacter>(GetOwner());
	if (!Owner) return;

	const auto DamagedHealthComponent = DamagedActor->FindComponentByClass<UCRPGHealthComponent>();
	if (!DamagedHealthComponent) return;

	DamagedActor->TakeDamage(DamageCalc(), FDamageEvent::FDamageEvent(), Owner->GetController(), Owner);

	TurnEnd(DamageCauser);
	
	Owner->PlayAttackAnim();

}

float UCRPGAttackComponent::DamageCalc()
{
	return BaseDamage;
}

void UCRPGAttackComponent::TurnEnd(AActor* DamageCauser)
{
	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->GetCurrentTurn() == ETurnUser::Player ? GameMode->SetCurrentTurn(ETurnUser::Enemy) : GameMode->SetCurrentTurn(ETurnUser::Player);
}