// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/CMainMenuController.h"
#include "MainMenu/CStartMenuWidget.h"
#include "MainMenu/CHostGameWidget.h"
#include "MainMenu/CJoinGameWidget.h"
#include "Utilities/UtilityList.h"
ACMainMenuController::ACMainMenuController()
{
	
	//付快胶目辑 荤侩
	bShowMouseCursor = true;
}

void ACMainMenuController::BeginPlay()
{
	//涝仿阑 UI父 涝仿啊瓷
	SetInputMode(FInputModeUIOnly());
	PageState = EMenuPageType::Start;
	ShowStartMenuWidget();
	CDisplayLog::Log(TEXT("ControllerBegin"));
}

void ACMainMenuController::StartMenu()
{
	ClearCurWidget();
	ShowStartMenuWidget();
	PageState = EMenuPageType::Start;

}

void ACMainMenuController::HostGame()
{
	ClearCurWidget();
	ShowHostGameWidget();
	PageState = EMenuPageType::Host;
}

void ACMainMenuController::JoinGame()
{
	ClearCurWidget();
	ShowJoinGameWidget();
	PageState = EMenuPageType::Join;
}

void ACMainMenuController::Back()
{

}

void ACMainMenuController::ShowStartMenuWidget()
{
	if (StartMenuWidget_C != nullptr)
	{
		//困连 积己
		StartMenuWidget = CreateWidget<UCStartMenuWidget>(this, StartMenuWidget_C);
		StartMenuWidget->AddToViewport();
	}
}

void ACMainMenuController::HideStartMenuWidget()
{
	if (StartMenuWidget != nullptr)
	{
		//困连 力芭
		StartMenuWidget->RemoveFromParent();
		//困连 昏力
		StartMenuWidget->Destruct();
	}
}

void ACMainMenuController::ShowHostGameWidget()
{
	if (HostGameWidget_C != nullptr)
	{
		//困连 积己
		HostGameWidget = CreateWidget<UCHostGameWidget>(this, HostGameWidget_C);
		HostGameWidget->AddToViewport();
	}
}

void ACMainMenuController::HideHostGameWidget()
{
	if (HostGameWidget != nullptr)
	{
		//困连 力芭
		HostGameWidget->RemoveFromParent();
		//困连 昏力
		HostGameWidget->Destruct();
	}
}

void ACMainMenuController::ShowJoinGameWidget()
{
	if (JoinGameWidget_C != nullptr)
	{
		//困连 积己
		JoinGameWidget = CreateWidget<UCJoinGameWidget>(this, JoinGameWidget_C);
		JoinGameWidget->AddToViewport();
	}
}

void ACMainMenuController::HideJoinGameWidget()
{
	if (JoinGameWidget != nullptr)
	{
		//困连 力芭
		JoinGameWidget->RemoveFromParent();
		//困连 昏力
		JoinGameWidget->Destruct();
	}
}

void ACMainMenuController::ClearCurWidget()
{
	switch (PageState)
	{
	case EMenuPageType::Start:
		HideStartMenuWidget();
		break;
	case EMenuPageType::Host:
		HideHostGameWidget();
		break;
	case EMenuPageType::Join:
		HideJoinGameWidget();
		break;

		
	default:
		break;

	}



}
