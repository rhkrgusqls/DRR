// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/AIController/BTActionTask/BTTSetAttack.h"
#include "DRR.h"
#include "GameFramework/Actor.h"
#include "EnemyCharacter/EnemyCharacterBase/EnemyCharacterBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTSetAttack::UBTTSetAttack()
{
}

EBTNodeResult::Type UBTTSetAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyCharacterBase* OwnerEnemy = Cast<AEnemyCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (OwnerEnemy)
	{
		AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
		OwnerEnemy->MeleeAttack(Target->GetActorLocation());
	}
	return EBTNodeResult::Type();
}
