// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldTravelPortal.generated.h"

UCLASS()
class DRR_API AWorldTravelPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldTravelPortal();

protected:


public:	
	UFUNCTION(BlueprintCallable, Category = "TravelWorld")
	void TravelWorldServer();

	void ServerTravelWorld();
};
