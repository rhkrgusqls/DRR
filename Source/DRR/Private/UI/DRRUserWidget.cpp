// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DRRUserWidget.h"
#include "Interface/DRRCharacterWidgetInterface.h"
#include "Components/ProgressBar.h"
#include "Animation/WidgetAnimation.h"
#include "MovieScene.h"
#include "UObject/UnrealType.h"

void UDRRUserWidget::UpdateHP(float NewHP)
{
	if (PlayerHPBar)
	{
		PlayerHPBar->SetPercent(NewHP / MaxHP);
		PlayAnimationByName(TEXT("HPChangedAnim"));
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
	
	//Inventory_UI = Cast<UUserWidget>(GetWidgetFromName(TEXT("WB_Inventory")));

	IDRRCharacterWidgetInterface* CharacterWidget = Cast<IDRRCharacterWidgetInterface>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}

	FillAnimationMap();

}

UWidgetAnimation* UDRRUserWidget::GetAnimationByName(const FName& AnimationName) const
{
	UWidgetAnimation* const* WidgetAnim = AnimationsMap.Find(AnimationName);
	if (WidgetAnim)
	{
		return *WidgetAnim;
	}

	return nullptr;
}

bool UDRRUserWidget::PlayAnimationByName(const FName& AnimationName, float StartAtTime, int32 NumLoopsToPlay, EUMGSequencePlayMode::Type PlayMode, float PlayBackSpeed)
{
	UWidgetAnimation* WidgetAnim = GetAnimationByName(AnimationName);
	if (WidgetAnim)
	{
		PlayAnimation(WidgetAnim, StartAtTime, NumLoopsToPlay, PlayMode, PlayBackSpeed);

		return true;
	}

	return false;
}

void UDRRUserWidget::FillAnimationMap()
{
	AnimationsMap.Empty();

	FProperty* Prop = GetClass()->PropertyLink;
	while (Prop != nullptr)
	{
		if (Prop->GetClass() == FObjectProperty::StaticClass())
		{
			FObjectProperty* ObjProp = static_cast<FObjectProperty*>(Prop);
			if (ObjProp->PropertyClass == UWidgetAnimation::StaticClass())
			{
				UObject* Obj = ObjProp->GetObjectPropertyValue_InContainer(this);


				UWidgetAnimation* WidgetAnim = Cast<UWidgetAnimation>(Obj);
				if (WidgetAnim != nullptr && WidgetAnim->MovieScene != nullptr)
				{
					FName AnimName = WidgetAnim->MovieScene->GetFName();
					AnimationsMap.Add(AnimName, WidgetAnim);
				}
			}
		}

		Prop = Prop->PropertyLinkNext;
	}
}
