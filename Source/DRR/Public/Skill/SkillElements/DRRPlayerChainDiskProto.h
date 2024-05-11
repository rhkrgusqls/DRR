// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DRRPlayerChainDiskProto.generated.h"

UCLASS()
class DRR_API ADRRPlayerChainDiskProto : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADRRPlayerChainDiskProto();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
