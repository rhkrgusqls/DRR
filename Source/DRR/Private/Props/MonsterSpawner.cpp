// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/MonsterSpawner.h"
#include "Public/EnemyCharacter/EnemyCharacterBase/EnemyCharacterBase.h"
#include "Components/BoxComponent.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Body = CreateDefaultSubobject<UBoxComponent>(TEXT("BodyBox"));
    Body->SetBoxExtent(FVector(0, 0, 0));
    Body->SetCollisionProfileName("NoCollision");
    RootComponent = Body;
    static ConstructorHelpers::FClassFinder<ACharacter> ObSpawnCharacter(TEXT("/Script/CoreUObject.Class'/Script/DRR.WarriorGoblin'"));
    if (ObSpawnCharacter.Class)
    {
        ASpawnCharacter = ObSpawnCharacter.Class;
    }
}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
    Super::BeginPlay();

    FTimerHandle SpawnTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AMonsterSpawner::SpawnCharacter, 10.0f, false);
}

void AMonsterSpawner::SpawnCharacter()
{
    if (HasAuthority())
    {
        if (ASpawnCharacter)
        {

            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;

            FVector SpawnLocation = GetActorLocation() + FVector(0, 0, 100);
            FRotator SpawnRotation = GetActorRotation();

            GetWorld()->SpawnActor<ACharacter>(ASpawnCharacter, SpawnLocation, SpawnRotation, SpawnParams);

        }
    }
}

// Called every frame
void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

