// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DRRGameState.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ADRRGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	ADRRGameState();
	virtual void BeginPlay() override;
	TArray<TObjectPtr<class ACharacterBase>> GetAnotherPlayerCharacters(AController* CurrentPlayerController);

};
