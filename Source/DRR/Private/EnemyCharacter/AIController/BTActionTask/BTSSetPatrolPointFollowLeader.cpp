// Include necessary header files
#include "EnemyCharacter/AIController/BTActionTask/BTSSetPatrolPointFollowLeader.h"
#include "DRR.h"
#include "GameFramework/Actor.h"
#include "EnemyCharacter/EnemyCharacterBase/EnemyCharacterBase.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "GameManager/EnemyManager.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Perception/AISense.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AIPerceptionSystem.h"

// Constructor for the UBTSSetPatrolPointFollowLeader class
UBTSSetPatrolPointFollowLeader::UBTSSetPatrolPointFollowLeader()
{
    // Constructor body (currently empty)
}

// Override TickNode method for the behavior tree node
void UBTSSetPatrolPointFollowLeader::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    // Cast the controlling pawn to AEnemyCharacterBase
    AEnemyCharacterBase* ControllingPawn = Cast<AEnemyCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());

    // If controlling pawn is null, return
    if (ControllingPawn == nullptr)
    {
        return;
    }

    // Get the world
    World = GetWorld();

    // If the world is valid, find an instance of AEnemyManager
    if (World != nullptr)
    {
        for (TActorIterator<AEnemyManager> It(World); It; ++It)
        {
            Manager = *It;
        }
    }

    // If a valid Manager instance is found
    if (Manager != nullptr)
    {
        // Set the "PatrolPoint" blackboard key to the patrol point for the controlling pawn
        OwnerComp.GetBlackboardComponent()->SetValueAsVector("PatrolPoint", Manager->GetPatrolPoint(ControllingPawn->GetEnemyCharacterNum()));
    }

    // Return from the function
    return;
}