// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/CRPGBaseWidget.h"
#include "CRPGPlayerBattleWidget.generated.h"

class UProgressBar;
class UButton;
class UVerticalBox;
class UEditableTextBox;
class ACRPGBaseCharacter;
class UScrollBox;

UCLASS()
class CRPG_API UCRPGPlayerBattleWidget : public UCRPGBaseWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent(AActor* DamagedActor) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	ACRPGBaseCharacter* GetAIActor() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	ACRPGBaseCharacter* GetPlayerActor() const;

protected:
	virtual void NativeOnInitialized() override;

	virtual void SetBaseFunc() override;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* PlayerHealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* AIHealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	UButton* FightButton;

	UPROPERTY(meta = (BindWidget), EditDefaultsOnly)
	UVerticalBox* SkillButtonsBox;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> SkillButtonClass;

	UPROPERTY(meta = (BindWidget))
	UButton* ItemButton;

	UPROPERTY(meta = (BindWidget), EditDefaultsOnly)
	UScrollBox* ItemScrollBox;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> ItemButtonClass;

	UPROPERTY(meta = (BindWidget))
	UButton* RunButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor GoodColor = FLinearColor::Blue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor BadColor = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float ColorChange = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Run", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float RunSuccess = 0.7f;

private:
	void UpdateHealthBar(AActor* DamagedActor);

	void OnHealthChanged(AActor* DamageCauser, AActor* DamagedActor);
	
	UFUNCTION()
	void ToggleFightButton();

	UFUNCTION()
	void ToggleItemButton();

	UFUNCTION()
	void TryEscapeBattle();
	void EscapeSuccess();
	void EscapeFail();

	void CreateSkillButtons();
	void CreateItemButtons();
};
