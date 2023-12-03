// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CRPGItemButtonWidget.h"

#include "Components/Button.h"
#include "CRPGGameModeBase.h"
#include "Components/TextBlock.h"
#include "CRPGGameModeBase.h"
#include "Character/CRPGBaseCharacter.h"
#include "Character/CRPGPlayerCharacter.h"
#include "Components/CRPGItemComponent.h"

void UCRPGItemButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ItemButton)
	{
		ItemButton->OnClicked.AddDynamic(this, &UCRPGItemButtonWidget::ItemClick);
	}

	if (ItemText)
	{
		ItemSetting();
	}

}

void UCRPGItemButtonWidget::ItemClick()
{
	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto Player = GameMode->GetPlayerCharacter();
	if (!Player) return;

	const auto PlayerCharacter = Cast<ACRPGPlayerCharacter>(Player);
	if (!PlayerCharacter) return;

	PlayerCharacter->UseItem(ItemData.Name);
	GetParent()->SetVisibility(ESlateVisibility::Hidden);
}

void UCRPGItemButtonWidget::ItemSetting()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto Player = GameMode->GetPlayerCharacter();
	if (!Player) return;

	const auto ItemComp = Cast<UCRPGItemComponent>(Player->GetComponentByClass(UCRPGItemComponent::StaticClass()));
	if (!ItemComp) return;

	if (ItemComp->GetSettingIndex() == ItemComp->GetItemNum())
	{
		ItemData = ItemComp->GetItem(ItemData.Name);
	}
	else
	{
		ItemData = ItemComp->GetItem(ItemComp->GetSettingIndex());
		ItemComp->SettingIndexAdd();
	}

}

void UCRPGItemButtonWidget::ItemTextSetting()
{
	FString str;

	str.Append(ItemData.Name.ToString());
	ItemText->SetText(FText::FromString(str));

	FString ToolTipStr;

	if (!ItemData.IsUsable && ItemData.LeftCount <= 0)
	{
		ToolTipStr.Append("Can't Use");
	}
	else if (ItemData.IsHealing)
	{
		ToolTipStr.Append("Healing : ");
		ToolTipStr.Append(FString::SanitizeFloat(ItemData.HealAmount));
	}

	ItemButton->ToolTipText = FText::FromString(ToolTipStr);
}
