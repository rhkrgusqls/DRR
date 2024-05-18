// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TimerManager.h"
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

	void ShowLodingScreen();
	void DeleteLodingScreen();

	FORCEINLINE UUserWidget* GetLodingScreenWidget() { return LodingScreenWidget; }
	

	//UFUNCTION(BlueprintCallable, Category = Widget)
	//void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass); // Widget change function

	//TObjectPtr<class UWidgetComponent> LodingScreen;

	FTimerHandle ShowLodingTimer;
	FTimerHandle LodingTimer;

protected:
	
	TSubclassOf<UUserWidget> LodingScreenWidgetClass;
	UUserWidget* LodingScreenWidget;


private:

};
