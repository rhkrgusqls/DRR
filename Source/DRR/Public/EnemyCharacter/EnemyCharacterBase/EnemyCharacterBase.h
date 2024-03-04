// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase/CharacterBase.h"
#include "EnemyCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class AEnemyCharacterBase : public ACharacterBase
{
	GENERATED_BODY()
	
	AEnemyCharacterBase();

	FString EnemyName;
};
