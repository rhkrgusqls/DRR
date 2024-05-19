// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/PatrolPoint/PatrolPoint.h"
#include "GameManager/EnemyManager.h"



#include "DRR.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"





// Sets default values
APatrolPoint::APatrolPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APatrolPoint::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle DelayedFunctionHandle;
	GetWorldTimerManager().SetTimer(DelayedFunctionHandle, this, &APatrolPoint::SettingPT, 5.0f, false);

}

void APatrolPoint::SettingPT()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		for (TActorIterator<AEnemyManager> It(World); It; ++It)
		{
			Manager = *It;
		}
	}
	if (Manager != nullptr)
	{
		Manager->SetPatrolPoint(this);
	}
}
