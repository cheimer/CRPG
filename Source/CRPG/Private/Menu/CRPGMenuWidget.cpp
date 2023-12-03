// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/CRPGMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UCRPGMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UCRPGMenuWidget::StartClick);
	}
}

void UCRPGMenuWidget::StartClick()
{
	if (StartLevelName != "")
	{
		UGameplayStatics::OpenLevel(this, StartLevelName);
	}
}