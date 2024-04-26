// Fill out your copyright notice in the Description page of Project Settings.


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
AMeleeMonsterBase::AMeleeMonsterBase():ANormalMonster(0)
{

}

void AMeleeMonsterBase::MeleeAttack(FVector TargetLocation)
{
	Super::AEnemyCharacterBase::MeleeAttack(TargetLocation);
    // Random Index
    int RandomIndex = FMath::RandRange(0, 2);

    // Random Arrack
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

void AMeleeMonsterBase::MiddleAttack(FVector TargetLocation)
{
	Super::AEnemyCharacterBase::MeleeAttack(TargetLocation);
}

void AMeleeMonsterBase::LongAttack(FVector TargetLocation)
{
	Super::AEnemyCharacterBase::MeleeAttack(TargetLocation);
}

void AMeleeMonsterBase::ComboAttack()
{
    StartComboAttack();
}

void AMeleeMonsterBase::StartComboAttack()
{

    FVector StartLocation = GetActorLocation();
    FVector EndLocation = StartLocation + FVector(-100.0f, 0.0f, 0.0f);
    FQuat Rotation = FQuat::Identity;

    FCollisionObjectQueryParams ObjectQueryParams;
    ObjectQueryParams.AddObjectTypesToQuery(ECC_GameTraceChannel1);

    float SphereRadius = 50.0f;
    FCollisionShape CollisionShape = FCollisionShape::MakeSphere(SphereRadius);

    TArray<FOverlapResult> OverlapResults;

    bool bOverlap = GetWorld()->OverlapMultiByObjectType(
        OverlapResults,
        EndLocation,
        Rotation,
        ObjectQueryParams,
        CollisionShape
    );

    if (bOverlap)
    {
        for (const FOverlapResult& OverlapResult : OverlapResults)
        {
            AActor* HitActor = OverlapResult.GetActor();

            if (HitActor)
            {
                UE_LOG(LogTemp, Warning, TEXT("Attack"));             
                    APlayerCharacterBase* CastedPlayer = Cast<APlayerCharacterBase>(HitActor);
                    if (CastedPlayer)
                    {
                        CastedPlayer->ReciveAttack(20);
                    }               
            }
        }
    }
    DrawDebugSphere(GetWorld(), EndLocation, SphereRadius, 12, FColor::Blue, false, 5.0f);
        EndComboAttack();
}

void AMeleeMonsterBase::EndComboAttack()
{
    //ComboAttackHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMeleeMonsterBase::OnAttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("Attack"));
    if (OtherActor && OtherActor != this) 
    {
        APlayerCharacterBase* CastedPlayer = Cast<APlayerCharacterBase>(OtherActor);
        if (CastedPlayer)
        {
            CastedPlayer->ReciveAttack(20);
        }
    }
}

void AMeleeMonsterBase::StrongAttack()
{
}

void AMeleeMonsterBase::Guard()
{
}
