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

FVector AEnemyManager::GetPatrolPoint(int32 PatrolUnitNum)
{
	int32* MyGroup = MonsterNum.Find(PatrolUnitNum);
	int32 LeaderUnit=0;
	int32 Temp=1;


	if (*MyGroup != PatrolUnitNum)
	{
		for (std::size_t index = 1; index < MonsterNum.Num(); ++index)
		{
			int32* GroupPtr = MonsterNum.Find(index);
			if (GroupPtr == nullptr)
			{
				break;
			}
			else
			{
				LeaderUnit = *MyGroup;
			}
			
			if (*GroupPtr == *MyGroup)
			{
				Temp++;
			}

			if(PatrolUnitNum == index+1)
			{
				FRotator RotationOffset;
				FRotator RotationOffset2;
				if (Temp % 2 == 1)
				{
					RotationOffset = FRotator(0, -225, 0);
					Temp = Temp - 3;
				}
				else
				{
					RotationOffset = FRotator(0, 225, 0);
					Temp = Temp - 2;
				}
				FVector CurrentLocation = ArrayPatrolUnit[LeaderUnit-1]->GetActorLocation();
				
				FRotator CurrentRotation = ArrayPatrolUnit[LeaderUnit-1]->GetActorRotation();

				FVector Direction = FRotationMatrix(CurrentRotation + RotationOffset).GetUnitAxis(EAxis::X);
				FVector Direction2 = FRotationMatrix(CurrentRotation).GetUnitAxis(EAxis::X);

				float Distance = 200.0f;
				
				FVector Offset = Direction * Distance;

				Temp = Temp / 2;

				FVector Offset2 = Direction2 * Distance * -Temp;

				FVector PatrolLocation = CurrentLocation + Offset + Offset2;

				FPatrolPoint = FVector(PatrolLocation);
				break;
			}
			
		}
	}
	else
	{
		FVector CurrentLocation = ArrayPatrolUnit[PatrolUnitNum - 1]->GetActorLocation();
		FRotator CurrentRotation = ArrayPatrolUnit[PatrolUnitNum - 1]->GetActorRotation();
		FVector Direction = FRotationMatrix(CurrentRotation).GetUnitAxis(EAxis::X);
		float Distance = 200.0f;
		FVector Offset = Direction * Distance;
		FVector PatrolLocation = CurrentLocation + Offset;
		FPatrolPoint = PatrolLocation;
	}
	return FPatrolPoint;
}

int32 AEnemyManager::SetMonsterNum(AActor* Self)
{
	int32 Temp = 1;
    for (std::size_t index = 0; index < MonsterNum.Num(); ++index) {
		Temp++;
		
	}
	ArrayPatrolUnit.Add(Self);
	MonsterNum.Add(Temp,Temp);
	
	//return Temp;
	return Temp;
}

