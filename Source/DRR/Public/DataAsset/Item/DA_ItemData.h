// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "DA_ItemData.generated.h"

/**
 * 
 */

UCLASS()
class DRR_API UDA_ItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	int32 Amount;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
