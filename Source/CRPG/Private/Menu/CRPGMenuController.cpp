// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/CRPGMenuController.h"

void ACRPGMenuController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}