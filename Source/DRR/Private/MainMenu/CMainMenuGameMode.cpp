// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/CMainMenuGameMode.h"
#include "MainMenu/CMainMenuController.h"
ACMainMenuGameMode::ACMainMenuGameMode()
{
	PlayerControllerClass=ACMainMenuController::StaticClass();

	DefaultPawnClass = nullptr;
}
