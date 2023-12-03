// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CRPGCoreTypes.h"
#include "CRPGItemComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRPG_API UCRPGItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCRPGItemComponent();

protected:
	virtual void BeginPlay() override;

public:	
	int32 GetItemNum() const { return Items.Num(); }

	bool CanUseItem(FText ItemName) const;

	int32 GetItemIndex(FText ItemName) const;
	FItemData GetItem(FText ItemName) const;
	FItemData GetItem(int32 Index) const { return Items[SettingIndex]; }

	void UseItem(FText ItemName);

	int32 GetSettingIndex() { return SettingIndex; }
	void SettingIndexAdd() { SettingIndex++; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TArray<FItemData> Items;

	void UseHealItem(FItemData ItemData);

private:
	int32 SettingIndex = 0;
};
