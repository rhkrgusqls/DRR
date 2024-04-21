// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTSObserverLeaderPatrol.generated.h"

/**
 * 
 */
UCLASS()
class UBTSObserverLeaderPatrol : public UBTService
{
	GENERATED_BODY()
	UBTSObserverLeaderPatrol();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
