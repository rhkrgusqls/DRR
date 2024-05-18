// Include necessary header files
#include "EnemyCharacter/AIController/BTActionTask/BTTSetAttack.h"
#include "DRR.h"
#include "GameFramework/Actor.h"
#include "EnemyCharacter/EnemyCharacterBase/EnemyCharacterBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

// Constructor for the UBTTSetAttack class
UBTTSetAttack::UBTTSetAttack()
{
    // Constructor body (currently empty)
}

// Override ExecuteTask method for the behavior tree node
EBTNodeResult::Type UBTTSetAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Cast the owner of the AI controller to AEnemyCharacterBase
    AEnemyCharacterBase* OwnerEnemy = Cast<AEnemyCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());

    // If OwnerEnemy is valid
    if (OwnerEnemy)
    {
        // Get the target actor from the blackboard
        AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));

        if (Target == nullptr)
        {
            return EBTNodeResult::Failed;
        }

        // Perform a melee attack towards the target location
        int Length = OwnerComp.GetBlackboardComponent()->GetValueAsEnum("Length");
        if (Length==0)
        {
            OwnerEnemy->LongAttack(Target->GetActorLocation());
        }
        else if (Length == 1)
        {
            OwnerEnemy->MiddleAttack(Target->GetActorLocation());
        }
        else if (Length == 2)
        {
            OwnerEnemy->MeleeAttack(Target->GetActorLocation());
        }
    }

    // Return task result as succeeded
    return EBTNodeResult::Succeeded;
}