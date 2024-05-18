// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawner.generated.h"

UCLASS()
class DRR_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SpawnCharacter();
public:	
	// Called every frame
	TObjectPtr<class UBoxComponent> Body;

	virtual void Tick(float DeltaTime) override;
	TSubclassOf <ACharacter> ASpawnCharacter;
};
