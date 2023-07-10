// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CRPGPlayerFieldWidget.h"
#include "Components/CRPGHealthComponent.h"
#include "Character/CRPGPlayerCharacter.h"
#include "Components/ProgressBar.h"

void UCRPGPlayerFieldWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HealthProgressBar->SetFillColorAndOpacity(GoodColor);
}

float UCRPGPlayerFieldWidget::GetHealthPercent() const
{
	const auto Player = Cast<ACRPGPlayerCharacter>(GetOwningPlayerPawn());
	if (!Player) return 0.0f;

	const auto HealthComponent = Player->FindComponentByClass<UCRPGHealthComponent>();
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

void UCRPGPlayerFieldWidget::UpdateHealthBar()
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > ColorChange ? GoodColor : BadColor);
	}
}

void UCRPGPlayerFieldWidget::OnHealthChanged(AActor* DamageCauser, AActor* DamagedActor)
{
	UpdateHealthBar();
}


void UCRPGPlayerFieldWidget::SetBaseFunc()
{
	const auto Player = Cast<ACRPGPlayerCharacter>(GetOwningPlayerPawn());
	if (Player)
	{
		const auto PlayerHealthComponent = Player->FindComponentByClass<UCRPGHealthComponent>();
		if (PlayerHealthComponent && !PlayerHealthComponent->OnHealthChangeSignature.IsBoundToObject(this))
		{
			PlayerHealthComponent->OnHealthChangeSignature.AddUObject(this, &UCRPGPlayerFieldWidget::OnHealthChanged);
		}
	}
}