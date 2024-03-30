// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/DRRMainGameMode.h"
#include "Blueprint/UserWidget.h"

ADRRMainGameMode::ADRRMainGameMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MainHUDWidgetRef(TEXT("/Game/Asset/UI/WBP_MainHUD.WBP_MainHUD_C"));

	if (MainHUDWidgetRef.Class)
	{
		MainHUDWidgetClass = MainHUDWidgetRef.Class;
	}
}

void ADRRMainGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(MainHUDWidgetClass))
	{
		MainHUDWidget = Cast<UUserWidget>(CreateWidget(GetWorld(), MainHUDWidgetClass));

		if (IsValid(MainHUDWidget))
		{
			MainHUDWidget->AddToViewport();
		}
	}
}
