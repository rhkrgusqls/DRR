// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DRRUserWidget.h"
#include "Interface/DRRCharacterWidgetInterface.h"

void UDRRUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	IDRRCharacterWidgetInterface* CharacterWidget = Cast<IDRRCharacterWidgetInterface>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}
