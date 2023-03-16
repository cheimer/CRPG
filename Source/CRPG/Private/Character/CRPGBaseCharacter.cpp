// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CRPGBaseCharacter.h"
#include "Components/CRPGHealthComponent.h"
#include "Components/CRPGAttackComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/CRPGAttackAnimNotify.h"
#include "G:\UE\ShootThemUp\Intermediate\ProjectFiles\AnimUtils.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "CRPGGameModeBase.h"

ACRPGBaseCharacter::ACRPGBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UCRPGHealthComponent>("HealthComponent");
	AttackComponent = CreateDefaultSubobject<UCRPGAttackComponent>("AttackComponent");
}

void ACRPGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(AttackComponent);
	
	HealthComponent->OnDeathSignature.AddUObject(this, &ACRPGBaseCharacter::OnDeath);
	HealthComponent->OnHealthChangeSignature.AddUObject(this, &ACRPGBaseCharacter::OnHealthChange);

	auto AttackNotify = AnimUtils::FindNotifyByClass<UCRPGAttackAnimNotify>(AttackAnim);
	if (!AttackNotify) return;

	AttackNotify->OnNotifySignature.AddUObject(this, &ACRPGBaseCharacter::PlayDamagedAnim);
}

void ACRPGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACRPGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ACRPGBaseCharacter::GetDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;

	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

	return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z);
}

bool ACRPGBaseCharacter::IsRunning() const
{
	return false;
}

void ACRPGBaseCharacter::OnDeath()
{
	PlayAnimMontage(DeathAnim);

	GetCharacterMovement()->DisableMovement();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetLifeSpan(LifeSpanTime);
}

void ACRPGBaseCharacter::OnHealthChange(AActor* DamageCauser, AActor* DamagedActor)
{

}

void ACRPGBaseCharacter::PlayAttackAnim()
{
	PlayAnimMontage(AttackAnim);

}

void ACRPGBaseCharacter::PlayDamagedAnim(USkeletalMeshComponent* MeshComponent)
{
	if (!GetWorld()) return;
	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto AnimInstance = GetMesh()->GetAnimInstance();

	bool EnemyOrMe = UKismetMathLibrary::EqualEqual_ObjectObject(this, GameMode->GetAICharacter()) || 
		UKismetMathLibrary::EqualEqual_ObjectObject(this, GameMode->GetPlayerCharacter());

	if (HealthComponent->IsDead() || !AnimInstance || AnimInstance->IsAnyMontagePlaying() || !EnemyOrMe)
		return;

	int32 RandInt = FMath::RandRange(0, 2);
	if (DamagedAnimArray[RandInt])
	{
		PlayAnimMontage(DamagedAnimArray[RandInt]);
	}
}