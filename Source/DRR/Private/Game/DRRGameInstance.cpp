// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DRRGameInstance.h"
#include "Utilities/CCommandSubsystem.h"
#include "Utilities/Multiplay/CMultiplaySubsystem.h"
#include "Utilities/UtilityList.h"

UDRRGameInstance::UDRRGameInstance()
{
	
}

void UDRRGameInstance::Init()
{
	Super::Init();
	UCCommandSubsystem* Command = GetSubsystem<UCCommandSubsystem>();
	if (Command != nullptr)
	{
	}
}

void UDRRGameInstance::Hello()
{
	CLog::Log("Hello");
}

void UDRRGameInstance::Host()
{
	 GetSubsystem<UCMultiplaySubsystem>()->CreateSession(4, "FreeForAll");
}

void UDRRGameInstance::Join_Address()
{
}

void UDRRGameInstance::Find()
{
	 GetSubsystem<UCMultiplaySubsystem>()->MultiplayerOnFindSessionComplete.AddUObject(this, &UDRRGameInstance::FindFinish);
	 GetSubsystem<UCMultiplaySubsystem>()->FindSession(10000);
}

void UDRRGameInstance::Join(uint32 RoomNum)
{

	 GetSubsystem<UCMultiplaySubsystem>()->TryJoin(RoomNum);
}

void UDRRGameInstance::FindFinish(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bwasSuccessful)
{
	for (int i = 0; i < SessionResults.Num(); i++)
	{
		CDisplayLog::Log(TEXT("%d ¹ø ¹æ : "), i);
	}

	 GetSubsystem<UCMultiplaySubsystem>()->MultiplayerOnFindSessionComplete.Clear();

}
