// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/AIController/BTActionTask/BTSSetMovementSpeed.h"
#include "Public/CharacterBase/CharacterBase.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlackBoard")


UBTSSetMovementSpeed::UBTSSetMovementSpeed()
{
}

void UBTSSetMovementSpeed::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ACharacterBase* ControllingPawn = Cast<ACharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	
	if (ControllingPawn == nullptr)
	{
		return;
	}
	FVector FMovementPoint = OwnerComp.GetBlackboardComponent()->GetValueAsVector("PatrolPoint");
	float Distance = FVector::Dist(ControllingPawn->GetActorLocation(), FMovementPoint);
	if (Distance >= 150)
	{
		if(!OwnerComp.GetBlackboardComponent()->GetValueAsBool("IsImleader"))
		ControllingPawn->StartSprinting();
	}
	else if (Distance < 150)
	{
		ControllingPawn->StopSprinting();
	}
}
