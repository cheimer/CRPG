// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CRPGPlayerBattleWidget.h"
#include "Components/CRPGHealthComponent.h"
#include "Character/CRPGPlayerCharacter.h"
#include "AI/CRPGAICharacter.h"
#include "Components/ProgressBar.h"
#include "CRPGGameModeBase.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/CRPGAttackComponent.h"
#include "UI/CRPGSkillButtonWidget.h"
#include "UI/CRPGItemButtonWidget.h"
#include "UI/CRPGTextBoxWidget.h"
#include "Components/ScrollBox.h"
#include "Components/CRPGItemComponent.h"

void UCRPGPlayerBattleWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerHealthProgressBar->SetFillColorAndOpacity(GoodColor);
	AIHealthProgressBar->SetFillColorAndOpacity(GoodColor);

	if (FightButton)
	{
		FightButton->OnClicked.AddDynamic(this, &UCRPGPlayerBattleWidget::ToggleFightButton);
	}

	if (ItemButton)
	{
		ItemButton->OnClicked.AddDynamic(this, &UCRPGPlayerBattleWidget::ToggleItemButton);
	}

	if (RunButton)
	{
		RunButton->OnClicked.AddDynamic(this, &UCRPGPlayerBattleWidget::TryEscapeBattle);
	}

}

float UCRPGPlayerBattleWidget::GetHealthPercent(AActor* DamagedActor) const
{
	const auto CurrentCharacter = Cast<ACRPGBaseCharacter>(DamagedActor);
	if (!CurrentCharacter) return 0.0f;

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

ACRPGBaseCharacter* UCRPGPlayerBattleWidget::GetAIActor() const
{
	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	const auto AI = Cast<ACRPGAICharacter>(GameMode->GetAICharacter());
	return AI;
}

ACRPGBaseCharacter* UCRPGPlayerBattleWidget::GetPlayerActor() const
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

void UCRPGPlayerBattleWidget::ToggleFightButton()
{
	if (!SkillButtonsBox || !SkillButtonClass) return;

	if (SkillButtonsBox->GetChildrenCount() == 0)
	{
		CreateSkillButtons();
	}

	if (SkillButtonsBox->GetVisibility() == ESlateVisibility::Visible)
	{
		SkillButtonsBox->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		SkillButtonsBox->SetVisibility(ESlateVisibility::Visible);

		const auto SkillButtons = SkillButtonsBox->GetAllChildren();

		for (const auto SkillButton : SkillButtons)
		{
			const auto SBWidget = Cast<UCRPGSkillButtonWidget>(SkillButton);
			if (!SBWidget)
			{
				continue;
			}

			SBWidget->SkillSetting();
			SBWidget->SkillTextSetting();
		}
	}
}

void UCRPGPlayerBattleWidget::CreateSkillButtons()
{
	const auto Player = GetPlayerActor();
	if (!Player) return;

	for (int idx = 0; idx < Player->SkillNum; idx++)
	{
		const auto SkillButton = CreateWidget<UCRPGSkillButtonWidget>(GetWorld(), SkillButtonClass);

		if (SkillButton)
		{
			SkillButtonsBox->AddChild(SkillButton);
		}
	}
}

void UCRPGPlayerBattleWidget::ToggleItemButton()
{
	if (!ItemScrollBox || !ItemButtonClass) return;

	if (ItemScrollBox->GetChildrenCount() == 0)
	{
		CreateItemButtons();
	}

	if (ItemScrollBox->GetVisibility() == ESlateVisibility::Visible)
	{
		ItemScrollBox->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		ItemScrollBox->SetVisibility(ESlateVisibility::Visible);

		const auto ItemButtons = ItemScrollBox->GetAllChildren();

		for (const auto ItemButtonIndex : ItemButtons)
		{
			const auto IBWidget = Cast<UCRPGItemButtonWidget>(ItemButtonIndex);
			if (!IBWidget)
			{
				continue;
			}

			IBWidget->ItemSetting();
			IBWidget->ItemTextSetting();
		}
	}
}

void UCRPGPlayerBattleWidget::CreateItemButtons()
{
	const auto Player = GetPlayerActor();
	if (!Player) return;

	const auto ItemComp = Cast<UCRPGItemComponent>(Player->GetComponentByClass(UCRPGItemComponent::StaticClass()));
	if (!ItemComp) return;

	for (int idx = 0; idx < ItemComp->GetItemNum(); idx++)
	{
		const auto ItemButtonWidget = CreateWidget<UCRPGItemButtonWidget>(GetWorld(), ItemButtonClass);

		if (ItemButtonWidget)
		{
			ItemScrollBox->AddChild(ItemButtonWidget);
		}
	}
}

void UCRPGPlayerBattleWidget::TryEscapeBattle()
{
	if (!GetWorld()) return;

	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	if (GameMode->GetCurrentTurn() == ETurnUser::Enemy)
		return;

	float RandNum = FMath::RandRange(0.0f, 1.0f);

	if (RandNum <= RunSuccess)
	{
		EscapeSuccess();
	}
	else
	{
		EscapeFail();
	}

}

void UCRPGPlayerBattleWidget::EscapeSuccess()
{
	if (!GetWorld()) return;

	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto Player = GetPlayerActor();
	if (!Player) return;

	Player->StatusStringSet("Escape Success");
	GameMode->EscapeBattle();
}

void UCRPGPlayerBattleWidget::EscapeFail()
{
	if (!GetWorld()) return;

	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto Player = GameMode->GetPlayerCharacter();
	if (!Player) return;

	const auto AttackComp = Cast<UCRPGAttackComponent>(Player->GetComponentByClass(UCRPGAttackComponent::StaticClass()));
	if (!AttackComp) return;

	Player->StatusStringSet("Escape Fail");

	AttackComp->TurnEnd();
}
