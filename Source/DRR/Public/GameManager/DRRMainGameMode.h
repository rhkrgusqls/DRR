// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
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

	virtual void BeginPlay() override;

	FORCEINLINE UUserWidget* GetMainHUDWidget() { return MainHUDWidget; }
	FORCEINLINE UUserWidget* GetItemListWidget() { return ItemListWidget; }
	FORCEINLINE UUserWidget* GetItemCardWidget() { return ItemCardWidget; }
	FORCEINLINE UUserWidget* GetActAlertWidget() { return InteractAlert; }

protected:
	TSubclassOf<UUserWidget> MainHUDWidgetClass;
	UUserWidget* MainHUDWidget;

	//Collected Item Alert List UI
	TSubclassOf<UUserWidget> ItemListWidgetClass;
	UUserWidget* ItemListWidget;
	FTimerHandle TimerHandle;

	//ItemCard content UI(Used inside of Collected Item Alert List UI)
	TSubclassOf<UUserWidget> ItemCardWidgetClass;
	UUserWidget* ItemCardWidget;

	//Interact Alert UI
	TSubclassOf<UUserWidget> InteractAlertClass;
	UUserWidget* InteractAlert;

private:
	UPROPERTY()
	class UDataTable* ItemDataTable;
};
