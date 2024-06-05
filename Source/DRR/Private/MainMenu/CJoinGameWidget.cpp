// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/CJoinGameWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"

#include "MainMenu/CSessionBoxWidget.h"
#include "MainMenu/CMainMenuController.h"

#include "Utilities/Multiplay/CMultiplaySubsystem.h"
#include "Utilities/UtilityList.h"

void UCJoinGameWidget::FindButtonClicked()
{
    UCMultiplaySubsystem* MultiSubsystem = GetGameInstance()->GetSubsystem<UCMultiplaySubsystem>();
    if (MultiSubsystem)
    {
        MultiSubsystem->MultiplayerOnFindSessionComplete.AddUObject(this, &UCJoinGameWidget::FindFinish);
        MultiSubsystem->FindSession(10, FApp::GetProjectName());
    }
}

void UCJoinGameWidget::FindFinish(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bwasSuccessful)
{

    UCMultiplaySubsystem* MultiSubsystem = GetGameInstance()->GetSubsystem<UCMultiplaySubsystem>();

    


    for (int i = 0; i < SessionResults.Num(); i++)
    {

        FString SessionName = SessionResults[i].GetSessionIdStr();
        int32 CurrentPlayers = SessionResults[i].Session.NumOpenPublicConnections;
        int32 MaxPlayers = SessionResults[i].Session.SessionSettings.NumPublicConnections;

        OnSessionFound(SessionName, CurrentPlayers, MaxPlayers, i);


    }

    MultiSubsystem->MultiplayerOnFindSessionComplete.Clear();

}
void UCJoinGameWidget::OnSessionFound(const FString& SessionName, int32 CurrentPlayers, int32 MaxPlayers, int32 SessionIndex)
{
    if (SessionListScrollBox)
    {
        UCSessionBoxWidget* SessionBox = NewObject< UCSessionBoxWidget>(this);
        SessionBox->Init(SessionIndex, CurrentPlayers, MaxPlayers, SessionName);


        SessionListScrollBox->AddChild(SessionBox);

    }
}


void UCJoinGameWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (FindButton)
    {
        FindButton->OnClicked.AddDynamic(this, &UCJoinGameWidget::FindButtonClicked);
    }
}

void UCJoinGameWidget::JoinButtonClicked()
{
   
}

void UCJoinGameWidget::BackBtnClicked()
{
    ACMainMenuController* temp= Cast<ACMainMenuController>(GetWorld()->GetFirstPlayerController());
   
}
