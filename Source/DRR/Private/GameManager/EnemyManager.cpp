// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/EnemyManager.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyManager::SetGroupNum(int32 MonsterNumber, int32 FindedMonsterNumber)
{
	int32* GroupPtr = MonsterNum.Find(MonsterNumber);
	int32* FindGroupPtr = MonsterNum.Find(FindedMonsterNumber);
	if(GroupPtr&&FindGroupPtr)
	{
		if (GroupPtr > FindGroupPtr)
		{
			*GroupPtr = *FindGroupPtr;
		}
	}

}

void AEnemyManager::NullGroup(int32 MonsterNumber)
{
	int32* GroupPtr = MonsterNum.Find(MonsterNumber);
	if (GroupPtr)
	{
		*GroupPtr = MonsterNumber;
	}
}

FVector AEnemyManager::GetPatrolPoint(AActor* PatrolUnit)
{
	return FVector(1,1,1);
}

int32 AEnemyManager::SetMonsterNum()
{
	int32 Temp = 1;
    for (std::size_t index = 0; index < MonsterNum.Num(); ++index) {
		Temp++;
		
	}

	MonsterNum.Add(Temp,Temp);
	
	//return Temp;
	return Temp;
}

