// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Public/GameManager/EnemyManager.h"
#include "PatrolPoint.generated.h"

UCLASS()
class DRR_API APatrolPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SettingPT();

public:	
	TObjectPtr<class UBoxComponent> Body;
	AEnemyManager* Manager;

};
