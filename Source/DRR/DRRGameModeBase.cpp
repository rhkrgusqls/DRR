// Copyright Epic Games, Inc. All Rights Reserved.


#include "DRRGameModeBase.h"

ADRRGameModeBase::ADRRGameModeBase()
{
	//Super::AGameModeBase();
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Game/Blueprints/Character/BP_PlayerCharacterBase.BP_PlayerCharacterBase"));
	//DefaultPawnClass Setting
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	//PlayerControllerClass Setting
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/DRR.ABPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}
