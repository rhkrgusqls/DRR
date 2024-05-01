// Include necessary headers
#include "EnemyCharacter/EnemyCharacterBase/NormalMonsterBase/MeleeMonsterBase.h"
#include "EnemyCharacter/EnemyCharacterBase/NormalMonster.h"
#include "EnemyCharacter/EnemyCharacterBase/EnemyCharacterBase.h"
#include "PlayerCharacter/PlayerCharacterBase/PlayerCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
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

void AMeleeMonsterBase::ComboAttack()
{
    ComboAttackCount();
}

void AMeleeMonsterBase::ComboAttackCount()
{
    
    if (!IsAttack)
    {
        IsAttack = true;
        if (ComboCount == 0)
        {
            StartComboAttack();
        }
        else if (ComboCount >= 1 && ComboCount <= MaxComboCount)
        {
            ComboAttackProcess();
        }
        else
        {
            ComboCount = 0;
        }
    }

}

// Function to start combo attack
void AMeleeMonsterBase::StartComboAttack()
{
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    AnimInstance->Montage_Play(NormalAttackMontage, AttackSpeed);

    FOnMontageEnded EndDelegate;
    EndDelegate.BindUObject(this, &AMeleeMonsterBase::EndComboAttack);
    AnimInstance->Montage_SetEndDelegate(EndDelegate, NormalAttackMontage);
}

void AMeleeMonsterBase::ComboAttackProcess()
{

}

// Function to end combo attack
void AMeleeMonsterBase::EndComboAttack(UAnimMontage* TargetMontage, bool bInterrupted)
{
    IsAttack = false;

    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AMeleeMonsterBase::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
        APlayerCharacterBase* HitPlayer = Cast<APlayerCharacterBase>(OtherActor);
        if (HitPlayer)
        {
            HitPlayer->ReciveAttack(physicsAttack);
        }
}

// Function for strong attack
void AMeleeMonsterBase::StrongAttack()
{

}

// Function for guarding
void AMeleeMonsterBase::Guard()
{

}