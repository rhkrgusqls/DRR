// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/AIController/BTActionTask/CreateNoiseForMakeGroup.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Perception/AISense.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AIPerceptionSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UCreateNoiseForMakeGroup::UCreateNoiseForMakeGroup()
{
}

EBTNodeResult::Type UCreateNoiseForMakeGroup::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}
	else
	{
		//FAISenseID NoiseSenseID = UAISense_Hearing::ID;
		FName Tag = ("Friend");
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), ControllingPawn->GetActorLocation(), 0.5f, ControllingPawn, 0.0f, Tag);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
