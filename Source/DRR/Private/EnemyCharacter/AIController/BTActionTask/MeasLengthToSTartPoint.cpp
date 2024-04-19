// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter/AIController/BTActionTask/MeasLengthToSTartPoint.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UMeasLengthToSTartPoint::UMeasLengthToSTartPoint()
{
}

EBTNodeResult::Type UMeasLengthToSTartPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("StartPoint"));
	float Temp = FVector::Dist(ControllingPawn->GetActorLocation(), Origin);
	if ( Temp >= 1000.0f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("MoveStartPoint", true);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("MoveStartPoint",false);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
