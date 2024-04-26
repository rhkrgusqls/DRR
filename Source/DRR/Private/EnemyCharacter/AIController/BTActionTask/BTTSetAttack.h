// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTSetAttack.generated.h"

/**
 * 
 */
UCLASS()
class UBTTSetAttack : public UBTTaskNode
{
	GENERATED_BODY()
	UBTTSetAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
