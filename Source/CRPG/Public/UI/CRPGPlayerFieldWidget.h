// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CRPGBaseWidget.h"
#include "Blueprint/UserWidget.h"
#include "CRPGPlayerFieldWidget.generated.h"

class UProgressBar;

UCLASS()
class CRPG_API UCRPGPlayerFieldWidget : public UCRPGBaseWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;

protected:
	virtual void NativeOnInitialized() override;

	virtual void SetBaseFunc() override;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor GoodColor = FLinearColor::Blue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor BadColor = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float ColorChange = 0.3f;

private:
	void UpdateHealthBar();

	void OnHealthChanged(AActor* DamageCauser, AActor* DamagedActor);
};
