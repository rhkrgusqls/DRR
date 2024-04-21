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

void UDRRUserWidget::UpdateMP(float NewMP)
{
	if (PlayerMPBar)
	{
		PlayerMPBar->SetPercent(NewMP / MaxMP);
	}
}

void UDRRUserWidget::UpdateST(float NewST)
{
	if (PlayerSTBar)
	{
		PlayerSTBar->SetPercent(NewST / MaxST);
	}
}

void UDRRUserWidget::UpdateGold(int32 NewGold)
{
	GoldText = FText::AsNumber(NewGold);
	if (CurrentGold)
	{
		CurrentGold->SetText(GoldText);
	}
}

void UDRRUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//EnemyHPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("EnemyHPBar")));
	PlayerHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PlayerHPBar")));
	PlayerMPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PlayerMPBar")));
	PlayerSTBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PlayerSTBar")));
	CurrentGold = Cast<UTextBlock>(GetWidgetFromName(TEXT("CurrentGold")));

	IDRRCharacterWidgetInterface* CharacterWidget = Cast<IDRRCharacterWidgetInterface>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}

}
