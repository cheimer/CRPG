// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/CRPGBaseWidget.h"
#include "CRPGPlayerBattleWidget.generated.h"

class UProgressBar;
<<<<<<< HEAD
class UButton;
class UVerticalBox;
class UEditableTextBox;
class ACRPGBaseCharacter;
class UScrollBox;
=======
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57

UCLASS()
class CRPG_API UCRPGPlayerBattleWidget : public UCRPGBaseWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent(AActor* DamagedActor) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
<<<<<<< HEAD
	ACRPGBaseCharacter* GetAIActor() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	ACRPGBaseCharacter* GetPlayerActor() const;

=======
	AActor* GetAIActor() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	AActor* GetPlayerActor() const;
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
protected:
	virtual void NativeOnInitialized() override;

	virtual void SetBaseFunc() override;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* PlayerHealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* AIHealthProgressBar;

<<<<<<< HEAD
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

=======
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor GoodColor = FLinearColor::Blue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor BadColor = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float ColorChange = 0.3f;

<<<<<<< HEAD
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Run", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float RunSuccess = 0.7f;

=======
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
private:
	void UpdateHealthBar(AActor* DamagedActor);

	void OnHealthChanged(AActor* DamageCauser, AActor* DamagedActor);
	
<<<<<<< HEAD
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
=======
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
};
