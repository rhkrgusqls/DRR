// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/CHostGameWidget.h"
#include "MainMenu/CMainMenuController.h"

#include "Components/EditableTextBox.h"
#include "Components/SpinBox.h"
#include "Components/Button.h"
#include "Utilities/Multiplay/CMultiplaySubsystem.h"

void UCHostGameWidget::HostBtnClicked()
{
    if (SessionNameTextBox && MaxPlayersSpinBox)
    {
        FString SessionName = SessionNameTextBox->GetText().ToString();
        int32 MaxPlayers = (int32)MaxPlayersSpinBox->GetValue();

        UCMultiplaySubsystem* MultiSubsystem = GetGameInstance()->GetSubsystem<UCMultiplaySubsystem>();
        if (MultiSubsystem)
        {
            MultiSubsystem->CreateSession(4, "FreeForAll", FApp::GetProjectName(), SessionName);
        }
    }
}

void UCHostGameWidget::BackBtnClicked()
{
    GetMenuController()->HostGame();

}

void UCHostGameWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (HostBtn)
    {
        HostBtn->OnClicked.AddDynamic(this, &UCHostGameWidget::HostBtnClicked);
    }
}

ACMainMenuController* UCHostGameWidget::GetMenuController()
{
    if (GetWorld()->GetFirstPlayerController()==nullptr)
    {
        return nullptr;
    }
    ACMainMenuController* Temp = Cast<ACMainMenuController>(GetWorld()->GetFirstPlayerController());
    if (Temp == nullptr)
    {
        return nullptr;
        
    }
    return Temp;
}
