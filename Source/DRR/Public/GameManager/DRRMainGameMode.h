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


	virtual void PostLogin(APlayerController* newPlayer) override;

	void SetHUDWidgets(APlayerController* Player);

	FORCEINLINE UUserWidget* GetMainHUDWidget() { return MainHUDWidget; }
	FORCEINLINE UUserWidget* GetItemListWidget() { return ItemListWidget; }
	FORCEINLINE UUserWidget* GetItemCardWidget() { return ItemCardWidget; }
	FORCEINLINE UUserWidget* GetActAlertWidget() { return InteractAlert; }

	//UFUNCTION(BlueprintCallable, Category = Widget)
	//void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass); // Widget change function

	

protected:
	TSubclassOf<UUserWidget> MainHUDWidgetClass;
	UUserWidget* MainHUDWidget;

	//Collected Item Alert List UI
	TSubclassOf<UUserWidget> ItemListWidgetClass;
	UUserWidget* ItemListWidget;
	
	//ItemCard content UI(Used inside of Collected Item Alert List UI)
	TSubclassOf<UUserWidget> ItemCardWidgetClass;
	UUserWidget* ItemCardWidget;

	//Interact Alert UI
	TSubclassOf<UUserWidget> InteractAlertClass;
	UUserWidget* InteractAlert;

	FTimerHandle TimerHandle;

private:

};
