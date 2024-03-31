// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "MoveToTarget.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UMoveToTarget : public UBTTask_MoveTo
{
	GENERATED_BODY()
	UMoveToTarget();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
