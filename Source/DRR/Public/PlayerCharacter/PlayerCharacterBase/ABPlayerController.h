// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ABPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API AABPlayerController : public APlayerController
{
	GENERATED_BODY()

	AABPlayerController();
	
public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	//TSubclassOf<class > HUDWidgetClass;

	//UPROPERTY()
	//class UDRRUserWidget* HUDWidget;
	
	virtual void BeginPlay() override;

};
