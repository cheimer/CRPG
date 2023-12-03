// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CRPGHealthComponent.h"
#include "Camera/CameraShake.h"

UCRPGHealthComponent::UCRPGHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UCRPGHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);

	if (AActor* Owner = GetOwner())
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UCRPGHealthComponent::OnTakeDamage);
	}
}

void UCRPGHealthComponent::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0)
		return;

	SetHealth(Health - Damage);
	OnHealthChangeSignature.Broadcast(DamageCauser, DamagedActor);

	if (IsDead())
	{
		OnDeathSignature.Broadcast();
	}
	else
	{
		PlayCameraShake();
	}
}

void UCRPGHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
}

void UCRPGHealthComponent::PlayCameraShake()
{
	const auto Player = Cast<APawn>(GetOwner());
	if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

bool UCRPGHealthComponent::IsMaxHP()
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}

void UCRPGHealthComponent::HealHP(float HealAmount)
{
	Health = FMath::Clamp(Health + HealAmount, 0.0f, MaxHealth);
}
