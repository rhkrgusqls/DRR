// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/CStartMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UCStartMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (SinglePlayBtn != nullptr)
	{
		SinglePlayBtn->OnClicked.AddDynamic(this, &UCStartMenuWidget::OnSinglePlayClicked);
	}
	if (HostBtn != nullptr)
	{
		HostBtn->OnClicked.AddDynamic(this, &UCStartMenuWidget::OnHostClicked);
	}
	if (JoinBtn != nullptr)
	{
		JoinBtn->OnClicked.AddDynamic(this, &UCStartMenuWidget::OnJoinClicked);
	}
	if (ExitBtn != nullptr)
	{
		ExitBtn->OnClicked.AddDynamic(this, &UCStartMenuWidget::OnExitClicked);
	}

}

void UCStartMenuWidget::OnSinglePlayClicked()
{
	//UGameplayStatics::OpenLevel()
}

void UCStartMenuWidget::OnHostClicked()
{
}

void UCStartMenuWidget::OnJoinClicked()
{
}

void UCStartMenuWidget::OnExitClicked()
{
}
