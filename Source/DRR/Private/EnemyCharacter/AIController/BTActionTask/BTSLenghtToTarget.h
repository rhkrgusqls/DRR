// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTSLenghtToTarget.generated.h"

/**
 * 
 */
UCLASS()
class UBTSLenghtToTarget : public UBTService
{
	GENERATED_BODY()
	UBTSLenghtToTarget();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
