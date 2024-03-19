// GameManager.cpp

#include "GameManager/GameManager.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"


UGameManager::UGameManager()
{
	ElapsedTimer = 0.0f;
}

void UGameManager::CreateGameSession()
{
    IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
    if (OnlineSubsystem)
    {
        IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
        if (SessionInterface.IsValid())
        {
            FOnlineSessionSettings SessionSettings;
            SessionSettings.NumPublicConnections = 4; //Max Public connect
            SessionSettings.bShouldAdvertise = true;
            SessionSettings.bIsLANMatch = false;
            SessionSettings.bUsesPresence = true;

            // CreateSession
            SessionInterface->CreateSession(0, TEXT("MySessionName"), SessionSettings);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Can't Get Session Interface"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Can't load OnlinSubSystem"));
    }
}

void UGameManager::FindGameSessions()
{
    IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
    if (OnlineSubsystem)
    {
        IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
        if (SessionInterface.IsValid())
        {
            FOnlineSessionSearch SessionSearch;

            // Set Search all Sessions
            SessionSearch.bIsLanQuery = false;
            SessionSearch.MaxSearchResults = 20; // Max SearchSession

            // Search Session
            SessionInterface->FindSessions(0, MakeShareable(new FOnlineSessionSearch(SessionSearch)));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Can't Get Session Interface"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Can't load OnlinSubSystem"));
    }
}

void UGameManager::StartTimer(UWorld* World)
{
	if (World)
	{
		World->GetTimerManager().SetTimer(TimerHandle, this, &UGameManager::UpdateTimer, 1.f, true);
	}
}

void UGameManager::StopTimer()
{
	if (TimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
}

void UGameManager::UpdateTimer()
{
	ElapsedTimer += 1.f;
}

float UGameManager::ReturnLevel()
{
	return ElapsedTimer;
}
