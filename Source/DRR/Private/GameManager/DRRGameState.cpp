// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/DRRGameState.h"
#include "GameManager/DRRPlayerState.h"
#include "CharacterBase/CharacterBase.h"

#include "Utilities/UtilityList.h"
ADRRGameState::ADRRGameState()
{
}
void ADRRGameState::BeginPlay()
{

	CDisplayLog::Log(TEXT("GameState Valid"));
}
TArray<TObjectPtr<ACharacterBase>> ADRRGameState::GetAnotherPlayerCharacters(AController* CurrentPlayerController)
{

	TArray<TObjectPtr<ACharacterBase>> Temp;
	APawn* CurrentPlayerPawn = CurrentPlayerController ? CurrentPlayerController->GetPawn() : nullptr;

	for (auto& i : PlayerArray)
	{
		APawn* PlayerPawn = i->GetPawn();
		ACharacterBase* CharTemp = Cast<ACharacterBase>(PlayerPawn);
		if (CharTemp != nullptr&&PlayerPawn!=CurrentPlayerPawn)
		{
			Temp.Add(CharTemp);
		}
		
	}


	return Temp;
}
