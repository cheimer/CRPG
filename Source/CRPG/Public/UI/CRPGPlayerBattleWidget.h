// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/CRPGBaseWidget.h"
#include "CRPGPlayerBattleWidget.generated.h"

class UProgressBar;

UCLASS()
class CRPG_API UCRPGPlayerBattleWidget : public UCRPGBaseWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent(AActor* DamagedActor) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	AActor* GetAIActor() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	AActor* GetPlayerActor() const;

protected:
	virtual void NativeOnInitialized() override;

	virtual void SetBaseFunc() override;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* PlayerHealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* AIHealthProgressBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor GoodColor = FLinearColor::Blue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor BadColor = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float ColorChange = 0.3f;

private:
	void UpdateHealthBar(AActor* DamagedActor);

	void OnHealthChanged(AActor* DamageCauser, AActor* DamagedActor);
	
};
