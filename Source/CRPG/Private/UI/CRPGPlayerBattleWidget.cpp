// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CRPGPlayerBattleWidget.h"
#include "Components/CRPGHealthComponent.h"
#include "Character/CRPGPlayerCharacter.h"
#include "AI/CRPGAICharacter.h"
#include "Components/ProgressBar.h"
#include "CRPGGameModeBase.h"

void UCRPGPlayerBattleWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerHealthProgressBar->SetFillColorAndOpacity(GoodColor);
	AIHealthProgressBar->SetFillColorAndOpacity(GoodColor);
}

float UCRPGPlayerBattleWidget::GetHealthPercent(AActor* DamagedActor) const
{
	const auto CurrentCharacter = Cast<ACRPGBaseCharacter>(DamagedActor);
	if (!CurrentCharacter) return 0.0f;

	// 여러마리 나오게 하는 설정 중에 2마리 잡고서 화면 전환 전에 튕김
	const auto HealthComponent = CurrentCharacter->FindComponentByClass<UCRPGHealthComponent>();
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

void UCRPGPlayerBattleWidget::UpdateHealthBar(AActor* DamagedActor)
{
	const auto CurrentHealthBar = Cast<ACRPGPlayerCharacter>(DamagedActor) ? PlayerHealthProgressBar : AIHealthProgressBar;

	if (CurrentHealthBar)
	{
		CurrentHealthBar->SetFillColorAndOpacity(GetHealthPercent(DamagedActor) > ColorChange ? GoodColor : BadColor);
	}
}

void UCRPGPlayerBattleWidget::OnHealthChanged(AActor* DamageCauser, AActor* DamagedActor)
{
	UpdateHealthBar(DamagedActor);
}

AActor* UCRPGPlayerBattleWidget::GetAIActor() const
{
	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	const auto AI = Cast<ACRPGAICharacter>(GameMode->GetAICharacter());
	return AI;
}

AActor* UCRPGPlayerBattleWidget::GetPlayerActor() const
{
	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	const auto Player = Cast<ACRPGPlayerCharacter>(GameMode->GetPlayerCharacter());
	return Player;
}

void UCRPGPlayerBattleWidget::SetBaseFunc()
{
	const auto Player = GetPlayerActor();
	if (Player)
	{
		const auto PlayerHealthComponent = Player->FindComponentByClass<UCRPGHealthComponent>();
		if (PlayerHealthComponent && !PlayerHealthComponent->OnHealthChangeSignature.IsBoundToObject(this))
		{
			PlayerHealthComponent->OnHealthChangeSignature.AddUObject(this, &UCRPGPlayerBattleWidget::OnHealthChanged);
		}
	}
	UpdateHealthBar(Player);

	//반복되는 내용
	const auto AI = GetAIActor();
	if (AI)
	{
		const auto AIHealthComponent = AI->FindComponentByClass<UCRPGHealthComponent>();
		if (AIHealthComponent && !AIHealthComponent->OnHealthChangeSignature.IsBoundToObject(this))
		{
			AIHealthComponent->OnHealthChangeSignature.AddUObject(this, &UCRPGPlayerBattleWidget::OnHealthChanged);
		}
	}
	UpdateHealthBar(AI);
}
