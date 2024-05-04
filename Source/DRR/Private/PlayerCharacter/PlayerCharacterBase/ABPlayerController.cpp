// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/PlayerCharacterBase/ABPlayerController.h"

AABPlayerController::AABPlayerController() 
{
	//static ConstructorHelpers::FClassFinder<UDRRUserWidget> UI_HUD_C(TEXT(""));
	//if (UI_HUD_C.Succeeded()) {
	//	HUDWidgetClass = UI_HUD_C.Class;
	//}
}


void AABPlayerController::BeginPlay()
{


	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

}


