// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CreateNoiseForMakeGroup.generated.h"

/**
 * 
 */
UCLASS()
class UCreateNoiseForMakeGroup : public UBTTaskNode
{
	GENERATED_BODY()
	
	UCreateNoiseForMakeGroup();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
