// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CRPGSkillButtonWidget.h"
#include "Components/Button.h"
#include "CRPGGameModeBase.h"
#include "Components/TextBlock.h"
#include "CRPGGameModeBase.h"
#include "Character/CRPGBaseCharacter.h"

void UCRPGSkillButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (SkillButton)
	{
		SkillButton->OnClicked.AddDynamic(this, &UCRPGSkillButtonWidget::SkillClick);
	}

	if (SkillText)
	{
		SkillSetting();
	}

}

void UCRPGSkillButtonWidget::SkillClick()
{
	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto Player = GameMode->GetPlayerCharacter();
	if (!Player) return;

	Player->ChangeCurrentSkill(SkillData.SkillIndex);
	GetParent()->SetVisibility(ESlateVisibility::Hidden);
}

void UCRPGSkillButtonWidget::SkillSetting()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto Player = GameMode->GetPlayerCharacter();
	if (!Player) return;

	if (SkillData.SkillIndex == -1)
	{
		SkillData = Player->GetSkill(Player->GetCurrentSkillIndex());
		Player->CurrentSkillIndexAdd();
	}
	else
	{
		SkillData = Player->GetSkill(SkillData.SkillIndex);
	}
}

void UCRPGSkillButtonWidget::SkillTextSetting()
{
	FString str;
	str.Append(SkillData.Name.ToString());

	if (SkillData.Limited)
	{
		str.Append(" ");
		str.Append(FString::FromInt(SkillData.LeftCount));
		str.Append("/");
		str.Append(FString::FromInt(SkillData.MaxCount));
	}

	SkillText->SetText(FText::FromString(str));
}
