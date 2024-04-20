// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

UCLASS()
class DRR_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetGroupNum(int32 MonsterNumber, int32 FindedMonsterNumber);

	void NullGroup(int32 MonsterNumber);

	FVector GetPatrolPoint(int32 PatrolUnitNum);

	FVector FPatrolPoint;

	int32 SetMonsterNum(AActor* Self);

	TArray<AActor*> PatrolPoint;
	TArray<AActor*> ArrayPatrolUnit;
	//MonsterNumber, GroupNumber
	TMap<int32, int32> MonsterNum;
};
