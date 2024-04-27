// Include necessary header files
#include "EnemyCharacter/AIController/BTActionTask/BTSSetMovementSpeed.h"
#include "Public/CharacterBase/CharacterBase.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

// UPROPERTY macro declaration for EditAnywhere and BlueprintReadWrite access
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlackBoard")

// Constructor for the UBTSSetMovementSpeed class
UBTSSetMovementSpeed::UBTSSetMovementSpeed()
{
    // Constructor body (currently empty)
}

// Override TickNode method for the behavior tree node
void UBTSSetMovementSpeed::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    // Get the controlling pawn (character)
    ACharacterBase* ControllingPawn = Cast<ACharacterBase>(OwnerComp.GetAIOwner()->GetPawn());

    // If controlling pawn is null, return
    if (ControllingPawn == nullptr)
    {
        return;
    }

    // Get the movement point from the blackboard
    FVector FMovementPoint = OwnerComp.GetBlackboardComponent()->GetValueAsVector("PatrolPoint");

    // Calculate the distance between the controlling pawn and the movement point
    float Distance = FVector::Dist(ControllingPawn->GetActorLocation(), FMovementPoint);

    // Determine the movement speed based on distance
    if (Distance >= 150)
    {
        // If the distance is 150 or more, check if the controlling pawn is not the leader
        if (!OwnerComp.GetBlackboardComponent()->GetValueAsBool("IsImleader"))
        {
            // Start sprinting if the controlling pawn is not the leader
            ControllingPawn->StartSprinting();
        }
    }
    else if (Distance < 150)
    {
        // If the distance is less than 150, stop sprinting
        ControllingPawn->StopSprinting();
    }
}