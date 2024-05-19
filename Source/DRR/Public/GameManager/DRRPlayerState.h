// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DRRPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ADRRPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ADRRPlayerState();

	virtual void BeginPlay() override;
public:
	
	
};
