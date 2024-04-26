// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTSSetMovementSpeed.generated.h"

/**
 * 
 */
UCLASS()
class UBTSSetMovementSpeed : public UBTService
{
	GENERATED_BODY()
	
	UBTSSetMovementSpeed();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
