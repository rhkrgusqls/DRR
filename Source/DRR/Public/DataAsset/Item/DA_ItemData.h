// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "DA_ItemData.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Potion,
	Weapon,
	Armor,
	ActiveItem
};

UCLASS()
class DRR_API UDA_ItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	
};

USTRUCT()
struct FData_Item : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Stackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int maximumStackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PreferInventoryHotbar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTransform> relativeTransformInHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTransform> relativeTransformEquiped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform DropTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool itemForEquipSlot;
};