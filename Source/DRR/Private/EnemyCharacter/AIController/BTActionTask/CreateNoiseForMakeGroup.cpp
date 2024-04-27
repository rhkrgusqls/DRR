// Include necessary header files
#include "EnemyCharacter/AIController/BTActionTask/CreateNoiseForMakeGroup.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Perception/AISense.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AIPerceptionSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

// Constructor for the UCreateNoiseForMakeGroup class
UCreateNoiseForMakeGroup::UCreateNoiseForMakeGroup()
{
    // Constructor body (currently empty)
}

// Override ExecuteTask method for the behavior tree node
EBTNodeResult::Type UCreateNoiseForMakeGroup::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Get the controlling pawn (character) from the AI controller
    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

    // If controlling pawn is null, return task failed
    if (ControllingPawn == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    else
    {
        // Set a tag for the noise event (e.g., "Friend")
        FName Tag = TEXT("Friend");

        // Report a noise event at the controlling pawn's location with specified loudness and decay rate
        UAISense_Hearing::ReportNoiseEvent(
            GetWorld(),                     // World context
            ControllingPawn->GetActorLocation(), // Noise location
            0.5f,                            // Loudness of the noise
            ControllingPawn,                 // Noise instigator
            0.0f,                            // Noise decay rate
            Tag                              // Noise tag
        );

        // Return task succeeded
        return EBTNodeResult::Succeeded;
    }

    // Return task failed as a fallback (should not be reached)
    return EBTNodeResult::Failed;
}