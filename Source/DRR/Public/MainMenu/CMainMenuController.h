// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"



#include "CMainMenuController.generated.h"

/**
 * 
 */

UENUM()
enum class EMenuPageType : uint8
{
	Start,
	Host,
	Join,
	Max
};

UCLASS()
class DRR_API ACMainMenuController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	ACMainMenuController();

	virtual void BeginPlay() override;

public:
	void StartMenu();
	void HostGame();
	void JoinGame();
	void Back();
protected:
	void ShowStartMenuWidget();
	void HideStartMenuWidget();

	void ShowHostGameWidget();
	void HideHostGameWidget();

	void ShowJoinGameWidget();
	void HideJoinGameWidget();

	void ClearCurWidget();
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UCStartMenuWidget> StartMenuWidget_C;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UCHostGameWidget> HostGameWidget_C;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UCJoinGameWidget> JoinGameWidget_C;

protected:
	UPROPERTY()
	TObjectPtr<class UCStartMenuWidget> StartMenuWidget;

	UPROPERTY()
	TObjectPtr<class UCHostGameWidget> HostGameWidget;

	UPROPERTY()
	TObjectPtr< class UCJoinGameWidget > JoinGameWidget;

	EMenuPageType PageState;

};
