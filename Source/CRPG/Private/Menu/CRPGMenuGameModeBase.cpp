// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/CRPGMenuGameModeBase.h"
#include "Menu/CRPGMenuController.h"
#include "Menu/CRPGMenuHUD.h"

ACRPGMenuGameModeBase::ACRPGMenuGameModeBase()
{
	PlayerControllerClass = ACRPGMenuController::StaticClass();
	HUDClass = ACRPGMenuHUD::StaticClass();

}