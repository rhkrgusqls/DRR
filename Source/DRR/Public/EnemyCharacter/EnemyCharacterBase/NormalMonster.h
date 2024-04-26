// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter/EnemyCharacterBase/EnemyCharacterBase.h"
#include "NormalMonster.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ANormalMonster : public AEnemyCharacterBase
{
	GENERATED_BODY()
public:
	ANormalMonster();
	ANormalMonster(int Type);
	
};
