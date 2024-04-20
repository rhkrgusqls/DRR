// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/AIController/BTActionTask/SetPatrolPoint.h"
#include "DRR.h"
#include "GameFramework/Actor.h"
#include "EnemyCharacter/EnemyCharacterBase/EnemyCharacterBase.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "GameManager/EnemyManager.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Perception/AISense.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AIPerceptionSystem.h"

USetPatrolPoint::USetPatrolPoint()
{
}

EBTNodeResult::Type USetPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyCharacterBase* ControllingPawn = Cast<AEnemyCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}
	World = GetWorld();
	if (World != nullptr)
	{
		for (TActorIterator<AEnemyManager> It(World); It; ++It)
		{
			Manager = *It;
		}
	}
	if (Manager != nullptr)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("PatrolPoint", Manager->GetPatrolPoint(ControllingPawn->GetEnemyCharacterNum()));
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
