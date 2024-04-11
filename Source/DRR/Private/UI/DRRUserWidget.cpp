// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DRRUserWidget.h"
#include "Interface/DRRCharacterWidgetInterface.h"
#include "Components/ProgressBar.h"

void UDRRUserWidget::UpdateHP(float NewHP)
{
	if (PlayerHPBar)
	{
		PlayerHPBar->SetPercent(NewHP / MaxHP);
	}
	/*
	if (EnemyHPProgressBar)
	{
		EnemyHPProgressBar->SetPercent(NewHP / MaxHP);
	}
	*/
}

void UDRRUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//EnemyHPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("EnemyHPBar")));
	PlayerHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PlayerHPBar")));

	IDRRCharacterWidgetInterface* CharacterWidget = Cast<IDRRCharacterWidgetInterface>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}
