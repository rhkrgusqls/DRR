// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/PlayerCharacterBase/Multiplayer/DRRMultiplayerManager.h"

#include "GameManager/DRRMainGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"
#include "PlayerCharacter/PlayerCharacterBase/PlayerCharacterBase.h"
#include "Utilities/Multiplay/CMultiplaySubsystem.h"

#include "Online.h"
#include "Utilities/UtilityList.h"



UDRRMultiplayerManager::UDRRMultiplayerManager()
{
    CDisplayLog::Log(TEXT("Multi Create"));
}

UDRRMultiplayerManager::~UDRRMultiplayerManager()
{
    MultiSubsystem = nullptr;
    CDisplayLog::Log(TEXT("Multi Destroy"));
}

void UDRRMultiplayerManager::HostSession(FString RoomName)
{

    MultiSubsystem->CreateSession(4, "FreeForAll", FApp::GetProjectName(), RoomName);

    

}

void UDRRMultiplayerManager::Join_Address()
{

}

void UDRRMultiplayerManager::FindSession()
{
    MultiSubsystem->MultiplayerOnFindSessionComplete.AddUObject(this, &UDRRMultiplayerManager::FindFinish);
    MultiSubsystem->FindSession(10000, FApp::GetProjectName());

}

void UDRRMultiplayerManager::JoinSession(uint32 RoomNum)
{

    MultiSubsystem->TryJoin(RoomNum);

}

void UDRRMultiplayerManager::LeaveSession()
{

    MultiSubsystem->LeaveSession();
}

void UDRRMultiplayerManager::FindFinish(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bwasSuccessful)
{

    FString RoomName;
    for (int i = 0; i < SessionResults.Num(); i++)
    {
         RoomName = MultiSubsystem->GetSessionInfo(SessionResults[i], FName("RoomName"));
         
         if (FString()!= RoomName)
         {
             CLog::Log(RoomName);
             CDisplayLog::Log(TEXT("%d 번 방 :%s "), i,*RoomName);
         }
         else
         {
             CDisplayLog::Log(TEXT("%d 번 방 : ? "), i);
         }

    }

    MultiSubsystem->MultiplayerOnFindSessionComplete.Clear();

}