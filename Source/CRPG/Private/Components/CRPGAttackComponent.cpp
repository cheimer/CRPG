// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CRPGAttackComponent.h"
#include "Components/CRPGHealthComponent.h"
#include "Character/CRPGBaseCharacter.h"
<<<<<<< HEAD
#include "DamageType/CRPGBloodingDamage.h"
=======
#include "DamageType/CRPGSmallBite.h"
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
#include "CRPGGameModeBase.h"
#include "CRPGCoreTypes.h"

UCRPGAttackComponent::UCRPGAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

<<<<<<< HEAD
=======

>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
void UCRPGAttackComponent::BeginPlay()
{
	Super::BeginPlay();

<<<<<<< HEAD
}

void UCRPGAttackComponent::Attack(ACRPGBaseCharacter* DamageCauser, ACRPGBaseCharacter* DamagedActor)
=======
	
}

void UCRPGAttackComponent::Attack(AActor* DamageCauser, AActor* DamagedActor)
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
{
	const auto Owner = Cast<ACRPGBaseCharacter>(GetOwner());
	if (!Owner) return;

	const auto DamagedHealthComponent = DamagedActor->FindComponentByClass<UCRPGHealthComponent>();
	if (!DamagedHealthComponent) return;

<<<<<<< HEAD
	//FDamageEvent DEvent;
	//DEvent.DamageTypeClass = UCRPGBloodingDamage::StaticClass();

	if (!DamageCauser->UseSkill())
		return;

	DamagedActor->TakeDamage(DamageCalc(DamageCauser), FDamageEvent::FDamageEvent(), Owner->GetController(), Owner);

	TurnEnd();
=======
	DamagedActor->TakeDamage(DamageCalc(), FDamageEvent::FDamageEvent(), Owner->GetController(), Owner);

	TurnEnd(DamageCauser);
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
	
	Owner->PlayAttackAnim();

}

<<<<<<< HEAD
float UCRPGAttackComponent::DamageCalc(ACRPGBaseCharacter* DamageCauser)
{
	return DamageCauser->GetSkill(DamageCauser->GetCurrentSkillIndex()).Damage;
}

void UCRPGAttackComponent::TurnEnd()
=======
float UCRPGAttackComponent::DamageCalc()
{
	return BaseDamage;
}

void UCRPGAttackComponent::TurnEnd(AActor* DamageCauser)
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
{
	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->GetCurrentTurn() == ETurnUser::Player ? GameMode->SetCurrentTurn(ETurnUser::Enemy) : GameMode->SetCurrentTurn(ETurnUser::Player);
}