// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_StatusData.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UDA_StatusData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	
	UPROPERTY(EditAnywhere, Category = "State")
	float MaxHP;

	UPROPERTY(EditAnywhere,  Category = "State")
	float MaxMP;

	UPROPERTY(EditAnywhere,  Category = "State")
	float MaxST;


	UPROPERTY(EditAnywhere,  Category = "State")
	float physicsAttack;

	UPROPERTY(EditAnywhere,  Category = "State")
	float physicsDef = 1;

	UPROPERTY(EditAnywhere,  Category = "State")
	float SprintSpeed ;

	UPROPERTY(EditAnywhere,  Category = "State")
	float WalkSpeed ;

	UPROPERTY(EditAnywhere,  Category = "State")
	float HPRegenSpeed;

};
