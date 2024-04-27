// Include necessary headers
#include "EnemyCharacter/EnemyCharacterBase/NormalMonsterBase/MeleeMonsterBase.h"
#include "EnemyCharacter/EnemyCharacterBase/NormalMonster.h"
#include "EnemyCharacter/EnemyCharacterBase/EnemyCharacterBase.h"
#include "PlayerCharacter/PlayerCharacterBase/PlayerCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

// Constructor for AMeleeMonsterBase
AMeleeMonsterBase::AMeleeMonsterBase() : ANormalMonster(0)
{
    // Initialization code can be added here
}

// Function for melee attack
void AMeleeMonsterBase::MeleeAttack(FVector TargetLocation)
{
    // Call the melee attack function of the base class
    Super::AEnemyCharacterBase::MeleeAttack(TargetLocation);

    // Generate a random index between 0 and 2
    int RandomIndex = FMath::RandRange(0, 2);

    // Execute a random attack based on the index
    switch (RandomIndex) {
    case 0:
        ComboAttack();
        break;
    case 1:
        StrongAttack();
        break;
    case 2:
        Guard();
        break;
    default:
        break;
    }
}

// Function for mid-range attack
void AMeleeMonsterBase::MiddleAttack(FVector TargetLocation)
{
    // Call the middle attack function of the base class
    Super::AEnemyCharacterBase::MeleeAttack(TargetLocation);
}

// Function for long-range attack
void AMeleeMonsterBase::LongAttack(FVector TargetLocation)
{
    // Call the long attack function of the base class
    Super::AEnemyCharacterBase::MeleeAttack(TargetLocation);
}

// Function for combo attack
void AMeleeMonsterBase::ComboAttack()
{
    StartComboAttack();
}

// Function to start combo attack
void AMeleeMonsterBase::StartComboAttack()
{
    // Set the start and end locations of the attack
    FVector StartLocation = GetActorLocation();
    FVector EndLocation = StartLocation + FVector(-100.0f, 0.0f, 0.0f);
    FQuat Rotation = FQuat::Identity;

    // Set collision query parameters
    FCollisionObjectQueryParams ObjectQueryParams;
    ObjectQueryParams.AddObjectTypesToQuery(ECC_GameTraceChannel1);

    float SphereRadius = 50.0f;
    FCollisionShape CollisionShape = FCollisionShape::MakeSphere(SphereRadius);

    // Create an array to store overlap results
    TArray<FOverlapResult> OverlapResults;

    // Perform overlap query
    bool bOverlap = GetWorld()->OverlapMultiByObjectType(
        OverlapResults,
        EndLocation,
        Rotation,
        ObjectQueryParams,
        CollisionShape
    );

    // Process the overlap results
    if (bOverlap)
    {
        for (const FOverlapResult& OverlapResult : OverlapResults)
        {
            AActor* HitActor = OverlapResult.GetActor();

            if (HitActor)
            {
                UE_LOG(LogTemp, Warning, TEXT("Attack"));
                // Check if the hit actor is a player character
                APlayerCharacterBase* CastedPlayer = Cast<APlayerCharacterBase>(HitActor);
                if (CastedPlayer)
                {
                    // Call the receive attack function on the player character
                    CastedPlayer->ReciveAttack(20);
                }
            }
        }
    }
    // Draw debug sphere at the end location
    DrawDebugSphere(GetWorld(), EndLocation, SphereRadius, 12, FColor::Blue, false, 5.0f);

    // End the combo attack
    EndComboAttack();
}

// Function to end combo attack
void AMeleeMonsterBase::EndComboAttack()
{
    // Disable collision for the combo attack hitbox
    // ComboAttackHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Function to handle attack overlap
void AMeleeMonsterBase::OnAttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("Attack"));
    // Ensure the other actor is valid and not this actor
    if (OtherActor && OtherActor != this)
    {
        // Check if the other actor is a player character
        APlayerCharacterBase* CastedPlayer = Cast<APlayerCharacterBase>(OtherActor);
        if (CastedPlayer)
        {
            // Call the receive attack function on the player character
            CastedPlayer->ReciveAttack(20);
        }
    }
}

// Function for strong attack
void AMeleeMonsterBase::StrongAttack()
{
    // Add your strong attack code here
}

// Function for guarding
void AMeleeMonsterBase::Guard()
{
    // Add your guard code here
}