// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/AIController/BTActionTask/BTSLenghtToTarget.h"
#include "Public/CharacterBase/CharacterBase.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Public/EnemyCharacter/AIController/BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTSLenghtToTarget::UBTSLenghtToTarget()
{
}

void UBTSLenghtToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ACharacterBase* ControllingPawn = Cast<ACharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
    // If controlling pawn is null, return
    if (ControllingPawn == nullptr)
    {
        return;
    }

    // Get the movement point from the blackboard
    AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
    if (Target == nullptr)
    {
        Cast<ABaseAIController>(ControllingPawn->GetController())->RemoveTarget();
        return;
    }
    else
    {
        float Distance = FVector::Dist(ControllingPawn->GetActorLocation(), Target->GetActorLocation());

        // Determine the movement speed based on distance
        if (Distance < 200)
        {
            ControllingPawn->StopSprinting();
            OwnerComp.GetBlackboardComponent()->SetValueAsEnum("Length", 2);

        }
        else if (200 <= Distance && Distance < 500)
        {
            ControllingPawn->StopSprinting();
            OwnerComp.GetBlackboardComponent()->SetValueAsEnum("Length", 1);
        }
        else if (500 <= Distance)
        {
            ControllingPawn->StartSprinting();
            OwnerComp.GetBlackboardComponent()->SetValueAsEnum("Length", 0);
        }
    }
}
