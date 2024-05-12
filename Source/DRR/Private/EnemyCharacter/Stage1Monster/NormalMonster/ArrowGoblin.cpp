// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/Stage1Monster/NormalMonster/ArrowGoblin.h"
#include "EnemyCharacter/Bullet/ArrowBullet.h"
#include "Engine/World.h"
#include "PlayerCharacter/PlayerCharacterBase/PlayerCharacterBase.h"

AArrowGoblin::AArrowGoblin():ANormalMonster(1)
{

}

void AArrowGoblin::BeginPlay()
{
    FActorSpawnParameters SpawnParams;
    SpawnParams.Instigator = this;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    SpawnParams.Owner = this;
    for (int i = 0; i <= 9; i++)
    {
        AArrowBullet* ArrowTemp = GetWorld()->SpawnActor<AArrowBullet>(AArrowBullet::StaticClass(), this->GetActorLocation(), this->GetActorRotation(),SpawnParams);
        Arrow.Add(ArrowTemp);
    }
    for (int i = 0; i <= 9; i++)
    {
        Arrow[i]->SetDamage(physicsAttack);
        Arrow[i]->SetActorHiddenInGame(true);
    }
}

void AArrowGoblin::MeleeAttack(FVector TargetLocation)
{
    // Call the melee attack function of the base class
    Super::AEnemyCharacterBase::MeleeAttack(TargetLocation);

    // Generate a random index between 0 and 2
    int RandomIndex = FMath::RandRange(0, 1);

    // Execute a random attack based on the index
    switch (RandomIndex) {
    case 0:

        break;
    case 1:
        break;
    case 2:

        break;
    default:
        break;
    }
}

void AArrowGoblin::MiddleAttack(FVector TargetLocation)
{
}

void AArrowGoblin::LongAttack(FVector TargetLocation)
{
    Super::AEnemyCharacterBase::LongAttack(TargetLocation);
    FireArrow(TargetLocation);
}

void AArrowGoblin::IncreaseDistance(FVector TargetLocation)
{
}

void AArrowGoblin::FireArrow(FVector TargetLocation)
{
    Arrow[ArrowNum]->SetActorHiddenInGame(false);
    
    if (ArrowNum > 9)
    {
        ArrowNum++;
    }
    else
    {
        ArrowNum = 0;
    }
}

void AArrowGoblin::KickAndRun(FVector TargetLocation)
{
}
