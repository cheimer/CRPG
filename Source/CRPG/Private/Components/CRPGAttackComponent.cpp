// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CRPGAttackComponent.h"
#include "Components/CRPGHealthComponent.h"
#include "Character/CRPGBaseCharacter.h"
#include "DamageType/CRPGBloodingDamage.h"
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

void UCRPGAttackComponent::Attack(ACRPGBaseCharacter* DamageCauser, ACRPGBaseCharacter* DamagedActor)
{
	const auto Owner = Cast<ACRPGBaseCharacter>(GetOwner());
	if (!Owner) return;

	const auto DamagedHealthComponent = DamagedActor->FindComponentByClass<UCRPGHealthComponent>();
	if (!DamagedHealthComponent) return;

	//FDamageEvent DEvent;
	//DEvent.DamageTypeClass = UCRPGBloodingDamage::StaticClass();

	if (!DamageCauser->UseSkill())
		return;

	DamagedActor->TakeDamage(DamageCalc(DamageCauser), FDamageEvent::FDamageEvent(), Owner->GetController(), Owner);

	TurnEnd();
	
	Owner->PlayAttackAnim();

}

float UCRPGAttackComponent::DamageCalc(ACRPGBaseCharacter* DamageCauser)
{
	return DamageCauser->GetSkill(DamageCauser->GetCurrentSkillIndex()).Damage;
}

void UCRPGAttackComponent::TurnEnd()
{
	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->GetCurrentTurn() == ETurnUser::Player ? GameMode->SetCurrentTurn(ETurnUser::Enemy) : GameMode->SetCurrentTurn(ETurnUser::Player);
}