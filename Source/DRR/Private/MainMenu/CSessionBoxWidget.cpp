// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/CSessionBoxWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Utilities/Multiplay/CMultiplaySubsystem.h"
#include "Utilities/UtilityList.h"

void UCSessionBoxWidget::Init(int32 index, int32 CurrentPlayers, int32 MaxPlayers, const FString& roomName)
{
	Index = index;
    RoomIndexTxt->SetText(FText::FromString(*FString::FromInt(index)));
    RoomNameTxt->SetText(FText::FromString(*roomName));
    RoomHeadCountTxt->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), CurrentPlayers, MaxPlayers)));



}

void UCSessionBoxWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
    JoinBtn->OnClicked.AddDynamic(this, &UCSessionBoxWidget::OnJoinBtnClicked);

}

void UCSessionBoxWidget::OnJoinBtnClicked()
{
    UCMultiplaySubsystem* MultiSubsystem = GetGameInstance()->GetSubsystem<UCMultiplaySubsystem>();
    if (MultiSubsystem)
    {
        MultiSubsystem->TryJoin(Index);
    }
}
