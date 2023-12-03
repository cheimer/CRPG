// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CRPGItemComponent.h"
#include "CRPGCoreTypes.h"
#include "CRPGGameModeBase.h"
#include "Character/CRPGBaseCharacter.h"
#include "Components/CRPGHealthComponent.h"
#include "Components/CRPGAttackComponent.h"

UCRPGItemComponent::UCRPGItemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UCRPGItemComponent::BeginPlay()
{
	Super::BeginPlay();

}

bool UCRPGItemComponent::CanUseItem(FText ItemName) const
{
	FItemData ItemData;

	for (FItemData ItemIndex : Items)
	{
		if (ItemIndex.Name.EqualTo(ItemName))
		{
			ItemData = ItemIndex;
			break;
		}
	}

	if (ItemData.IsUsable)
	{
		return true;
	}

	return false;
}


FItemData UCRPGItemComponent::GetItem(FText ItemName) const
{
	for (FItemData ItemIndex : Items)
	{
		if (ItemIndex.Name.EqualTo(ItemName))
		{
			return ItemIndex;
		}
	}

	//return 값을 어떻게 해야하나...
	UE_LOG(LogTemp, Warning, TEXT("Item Find Error Return 0 Index"));
	return Items[0];
}

int32 UCRPGItemComponent::GetItemIndex(FText ItemName) const
{
	for (int32 index = 0; index < GetItemNum(); index++)
	{
		if (Items[index].Name.EqualTo(ItemName))
			return index;
	}

	UE_LOG(LogTemp, Warning, TEXT("ItemIndex Find Error Return -1"));
	return -1;
}

void UCRPGItemComponent::UseItem(FText ItemName)
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto Player = GameMode->GetPlayerCharacter();
	if (!Player) return;

	FItemData CurrentItem = GetItem(ItemName);

	if (!CurrentItem.IsUsable || CurrentItem.LeftCount <= 0)
	{
		FString str = CurrentItem.Name.ToString();
		str.Append(" Can't Use");

		Player->StatusStringSet(str);
	}
	else if (CurrentItem.IsHealing)
	{
		UseHealItem(CurrentItem);
	}

}

void UCRPGItemComponent::UseHealItem(FItemData ItemData)
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto Player = GameMode->GetPlayerCharacter();
	if (!Player) return;

	const auto HealthComp = Cast<UCRPGHealthComponent>(Player->GetComponentByClass(UCRPGHealthComponent::StaticClass()));

	if (HealthComp->IsMaxHP())
	{
		FString str = "Max HP Can't Use Heal";
		Player->StatusStringSet(str);
	}
	else
	{
		HealthComp->HealHP(ItemData.HealAmount);
		const auto ItemDataIndex = GetItemIndex(ItemData.Name);
		Items[ItemDataIndex].LeftCount--;

		FString str = "Heal Potion Left ";
		str.Append(FString::FromInt(Items[ItemDataIndex].LeftCount));
		Player->StatusStringSet(str);

		const auto AttackComp = Cast<UCRPGAttackComponent>(Player->GetComponentByClass(UCRPGAttackComponent::StaticClass()));
		AttackComp->TurnEnd();
	}
}
