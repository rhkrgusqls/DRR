// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "GameManager/EnemyManager.h"
#include "BTSSetPatrolPointFollowLeader.generated.h"

/**
 * 
 */
UCLASS()
class UBTSSetPatrolPointFollowLeader : public UBTService
{
	GENERATED_BODY()

	UBTSSetPatrolPointFollowLeader();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	UWorld* World;

	AEnemyManager* Manager;
};
