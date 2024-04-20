// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GameManager/EnemyManager.h"
#include "SetPatrolPoint.generated.h"


/**
 * 
 */
UCLASS()
class USetPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()

	USetPatrolPoint();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UWorld* World;

	AEnemyManager* Manager;
};
