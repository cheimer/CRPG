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
<<<<<<< HEAD
=======
	
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
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
<<<<<<< HEAD
=======


>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
}

void UCRPGHealthComponent::SetHealth(float NewHealth)
{
<<<<<<< HEAD
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
=======
	NewHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);

	Health = NewHealth;

>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
}

void UCRPGHealthComponent::PlayCameraShake()
{
	const auto Player = Cast<APawn>(GetOwner());
	if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}
<<<<<<< HEAD

bool UCRPGHealthComponent::IsMaxHP()
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}

void UCRPGHealthComponent::HealHP(float HealAmount)
{
	Health = FMath::Clamp(Health + HealAmount, 0.0f, MaxHealth);
}
=======
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
