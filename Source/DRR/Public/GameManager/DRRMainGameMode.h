// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "UI/DRRMainPlayerHUD.h"
#include "DRRMainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ADRRMainGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ADRRMainGameMode();

public:
	virtual void BeginPlay() override;

protected:
	TSubclassOf<UUserWidget> MainHUDWidgetClass;

	UUserWidget* MainHUDWidget;
};
