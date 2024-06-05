// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/CLobbyGameMode.h"

#include "Lobby/CLobbyController.h"
ACLobbyGameMode::ACLobbyGameMode()
{

	PlayerControllerClass = ACLobbyController::StaticClass();

	DefaultPawnClass = nullptr;
}
