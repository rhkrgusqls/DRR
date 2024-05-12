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
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Engine/World.h"

// Constructor for AMeleeMonsterBase
AMeleeMonsterBase::AMeleeMonsterBase()
{
    // Initialization code can be added here
}

AMeleeMonsterBase::AMeleeMonsterBase(int Index) : ANormalMonster(Index)
{
}

// Function for melee attack
void AMeleeMonsterBase::MeleeAttack(FVector TargetLocation)
{
    // Call the melee attack function of the base class
    Super::AEnemyCharacterBase::MeleeAttack(TargetLocation);

    // Generate a random index between 0 and 2
    int RandomIndex = FMath::RandRange(0, 2);

    if (IsComboAttacking)
    {
        RandomIndex = 0;
    }

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

void AMeleeMonsterBase::CreateHitBoxBetweenBones(FName RightBoneName1, FName RightBoneName2, FName LeftBoneName1, FName LeftBoneName2)
{
    // Reference to Skeletal Mesh Component
    SkeletalMeshComp = FindComponentByClass<USkeletalMeshComponent>();
    if (!SkeletalMeshComp)
    {
        UE_LOG(LogTemp, Warning, TEXT("SkeletalMeshComponent not found."));
        return;
    }

    // Names of the bones
    BoneName1 = RightBoneName2;
    BoneName2 = RightBoneName1;

    // Get the positions of the bones
    BonePosition1 = SkeletalMeshComp->GetSocketLocation(BoneName1);
    BonePosition2 = SkeletalMeshComp->GetSocketLocation(BoneName2);

    // Calculate the midpoint and direction between the bones
    MidPoint = (BonePosition1 + BonePosition2) / 2;
    Direction = (BonePosition2 - BonePosition1).GetSafeNormal();

    FVector DifferenceRo = BonePosition1 - BonePosition2;

    FRotator RotationR = DifferenceRo.Rotation();

    FVector Difference = BonePosition1 - BonePosition2;


    float Distance = Difference.Size();

    // Set the size of the rectangular hitbox
    BoxExtent = FVector(Distance, 10.0f, 20.f);




    // Create and set up the collision box

    if (RightWeaponHitBox)
    {
        // Configure HitBox properties
        RightWeaponHitBox->SetBoxExtent(BoxExtent);
        RightWeaponHitBox->AttachToComponent(SkeletalMeshComp, FAttachmentTransformRules::KeepWorldTransform);


        RightWeaponHitBox->AttachToComponent(SkeletalMeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightBoneName1);

        RightWeaponHitBox->SetWorldLocation(MidPoint);
        RightWeaponHitBox->SetWorldRotation(GetRotationForBone(BonePosition1, BonePosition2));//RotationR);

        // Set the desired collision profile
        RightWeaponHitBox->SetCollisionProfileName(TEXT("NoCollision"));
        // Register the component to activate it
        RightWeaponHitBox->RegisterComponent();

        // Enable debug rendering
        RightWeaponHitBox->SetHiddenInGame(false);
    }

    // Reference to Skeletal Mesh Component
    SkeletalMeshComp2 = FindComponentByClass<USkeletalMeshComponent>();
    if (!SkeletalMeshComp2)
    {
        UE_LOG(LogTemp, Warning, TEXT("SkeletalMeshComponent not found."));
        return;
    }

    // Names of the bones
    BoneName3 = LeftBoneName2;
    BoneName4 = LeftBoneName1;

    // Get the positions of the bones
    BonePosition3 = SkeletalMeshComp->GetSocketLocation(BoneName3);
    BonePosition4 = SkeletalMeshComp->GetSocketLocation(BoneName4);

    // Calculate the midpoint and direction between the bones
    MidPoint = (BonePosition3 + BonePosition4) / 2;
    Direction = (BonePosition3 - BonePosition4).GetSafeNormal();

    FVector DifferenceRo2 = BonePosition3 - BonePosition4;

    FRotator RotationR2 = DifferenceRo2.Rotation();

    FVector Difference2 = BonePosition3 - BonePosition4;


    float Distance2 = Difference2.Size();

    // Set the size of the rectangular hitbox
    BoxExtent = FVector(Distance2, 10.0f, 20.0f);



    // Create and set up the collision box

    if (LeftWeaponHitBox)
    {
        // Configure HitBox properties
        LeftWeaponHitBox->SetBoxExtent(BoxExtent);
        LeftWeaponHitBox->AttachToComponent(SkeletalMeshComp, FAttachmentTransformRules::KeepWorldTransform);


        LeftWeaponHitBox->AttachToComponent(SkeletalMeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftBoneName2);

        LeftWeaponHitBox->SetWorldLocation(MidPoint);
        LeftWeaponHitBox->SetWorldRotation(GetRotationForBone(BonePosition3, BonePosition4));//RotationR);

        // Set the desired collision profile
        LeftWeaponHitBox->SetCollisionProfileName(TEXT("NoCollision"));

        // Register the component to activate it
        LeftWeaponHitBox->RegisterComponent();

        // Enable debug rendering
        LeftWeaponHitBox->SetHiddenInGame(false);
    }

    RightWeaponHitBox->OnComponentBeginOverlap.AddDynamic(this, &AMeleeMonsterBase::OnHit);
    LeftWeaponHitBox->OnComponentBeginOverlap.AddDynamic(this, &AMeleeMonsterBase::OnHit);
}

FRotator AMeleeMonsterBase::GetRotationForBone(FVector BoneX, FVector BoneY)
{
    FVector Direction3 = BoneX - BoneY;
    Direction3.Normalize();

    FRotator Rotation2 = Direction3.Rotation();
    return Rotation2;
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
        if (ComboCount == 1)
        {
            StartComboAttack();
            return;
        }
        else if (ComboCount >= 2 && ComboCount <= MaxComboCount)
        {
            ComboAttackProcess();
            return;
        }
        else
        {
            ComboCount = 1;
        }
    }

}

// Function to start combo attack
void AMeleeMonsterBase::StartComboAttack()
{
    IsComboAttacking = true;
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    AnimInstance->Montage_Play(NormalAttackMontage, AttackSpeed);

    FOnMontageEnded EndDelegate;
    EndDelegate.BindUObject(this, &AMeleeMonsterBase::EndComboAttack);
    AnimInstance->Montage_SetEndDelegate(EndDelegate, NormalAttackMontage);

    RightWeaponHitBox->SetCollisionProfileName(TEXT("EnemyAttack"));
}

void AMeleeMonsterBase::ComboAttackProcess()
{
   ComboCount = FMath::Clamp(ComboCount + 1, 1, MaxComboCount);
   if (ComboCount <= MaxComboCount)
   {
       FName NextSectionName = *FString::Printf(TEXT("Combo%d"), ComboCount);

       UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
       SetCollision();
       AnimInstance->Montage_JumpToSection(NextSectionName, NormalAttackMontage);
   }
}

void AMeleeMonsterBase::SetCollision()
{
}

// Function to end combo attack
void AMeleeMonsterBase::EndComboAttack(UAnimMontage* TargetMontage, bool bInterrupted)
{
    IsComboAttacking = false;
    IsAttack = false;
    ComboCount = 1;
    LeftWeaponHitBox->SetCollisionProfileName(TEXT("NoCollision"));
    RightWeaponHitBox->SetCollisionProfileName(TEXT("NoCollision"));
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
    HitedActor.Empty();
}

void AMeleeMonsterBase::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
        APlayerCharacterBase* HitPlayer = Cast<APlayerCharacterBase>(OtherActor);
        if (HitPlayer)
        {
            if (HitedActor.Contains(HitPlayer))
            {
                
            }
            else
            {
                HitPlayer->ReciveAttack(physicsAttack);
                HitedActor.Add(HitPlayer);
            }
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