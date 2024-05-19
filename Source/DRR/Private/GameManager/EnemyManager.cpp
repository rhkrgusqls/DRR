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
	FTimerHandle DelayedFunctionHandle;
	GetWorldTimerManager().SetTimer(DelayedFunctionHandle, this, &AEnemyManager::Logpat, 10.0f, false);
}

void AEnemyManager::Logpat()
{
	int32 NumPatrolPoints = PatrolPoint.Num();
	for (int32 i = 0; i < NumPatrolPoints; ++i)
	{
		if (PatrolPoint[i] != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("PatrolPoint[%d]: %s"), i, *PatrolPoint[i]->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("PatrolPoint[%d]: nullptr"), i);
		}
	}
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


	if (GroupPtr && FindGroupPtr)
	{
		if (*GroupPtr > *FindGroupPtr)
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

void AEnemyManager::SetDeadMonster(int32 MonsterNumber)
{
	IsDeadMonster[MonsterNumber] = true;
	ArrayPatrolUnit[MonsterNumber] = nullptr;
	/*			
	if(IsDeadMonster[index])
			{
				if (MyGroup == MonsterNum.Find(index))
				{
					*MyGroup = PatrolUnitNum;
				}
			}
	*/
}

void AEnemyManager::SetPatrolPoint(AActor* self)
{
	PatrolPoint.Add(self);
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
				if (ArrayPatrolUnit[LeaderUnit - 1]==nullptr)
				{
					break;
				}
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
				FVector CurrentLocation = ArrayPatrolUnit[LeaderUnit]->GetActorLocation();
				
				FRotator CurrentRotation = ArrayPatrolUnit[LeaderUnit]->GetActorRotation();

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
		Logpat();
		/*
		if (ClosestPatrolPoints[PatrolUnitNum].Num() == 0)
		{
			FPatrolPoint = ClosestPatrolPoints[PatrolUnitNum][0]->GetActorLocation();
		}
		/*----------------------------------------------------------------------------------------------------------------------------------------------------*/
		/*----------------------------------------------------------------------------------------------------------------------------------------------------*/
		//else
		//{
			FVector CurrentLocation = ArrayPatrolUnit[PatrolUnitNum]->GetActorLocation();
			FRotator CurrentRotation = ArrayPatrolUnit[PatrolUnitNum]->GetActorRotation();
			FVector Direction = FRotationMatrix(CurrentRotation).GetUnitAxis(EAxis::X);
			float Distance = 200.0f;
			FVector Offset = Direction * Distance;
			FVector PatrolLocation = CurrentLocation + Offset;
			FPatrolPoint = PatrolLocation;
		//}
		
		/*----------------------------------------------------------------------------------------------------------------------------------------------------*/
		/*----------------------------------------------------------------------------------------------------------------------------------------------------*/
	}
	return FPatrolPoint;
}

//Recive EnemyCharacterBase BeginPlay Event
int32 AEnemyManager::SetMonsterNum(AActor* Self)
{
	int32 Temp = 0;
    for (std::size_t index = 0; index < MonsterNum.Num(); ++index) {
		Temp++;
		if (IsDeadMonster[index] == NULL)
		{
			if(IsDeadMonster[index])
			{
				IsDeadMonster[index] = false;
				ArrayPatrolUnit[index] = Self;
				return Temp;
			}
		}
	}

	FVector LocationA = Self->GetActorLocation();

	TArray<AActor*> SortedPatrolPoints = PatrolPoint;
	TArray<AActor*> TempPoints;
	SortedPatrolPoints.Sort([LocationA](const AActor& Point1, const AActor& Point2) {
		return FVector::Dist(LocationA, Point1.GetActorLocation()) < FVector::Dist(LocationA, Point2.GetActorLocation());
		});

	for (int32 i = 0; i < FMath::Min(5, SortedPatrolPoints.Num()); ++i)
	{
		TempPoints.Add(SortedPatrolPoints[i]);
	}
	ClosestPatrolPoints.Add(TempPoints);
	IsDeadMonster.Add(false);
	ArrayPatrolUnit.Add(Self);
	MonsterNum.Add(Temp,Temp);
	
	//return Temp;
	return Temp;
}

