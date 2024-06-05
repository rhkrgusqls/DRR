// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "DA_ActData.generated.h"


UENUM()
enum class EActType : uint8
{
	ShortShot,
	Charging,
	Casting,
	Combo,
	Trigger
};

UENUM()
enum class EActCycleType : uint8
{
	Reverse,
	Constant,
	End
};
UENUM()
enum class EActCostType : uint8
{
	NoCost,
	OnlyFirst,
	EveryTime,
	End
};
/**
 * 
 */
UCLASS()
class DRR_API UDA_ActData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = Section)
	FString ActionName;

	UPROPERTY(EditAnywhere, Category = Animation)
	TObjectPtr<class UAnimMontage> ActionMontage;
	

	UPROPERTY(EditAnywhere, Category = Section)
	FString MontageSectionPrefix;

	UPROPERTY(EditAnywhere, Category = Section)
	float SkillCoefficient;

	UPROPERTY(EditAnywhere, Category = Section)
	uint8 MaxActCount;


	UPROPERTY(EditAnywhere, Category = Section)
	TArray<float> EffectiveFrameCount;


	UPROPERTY(EditAnywhere, Category = Section)
	TArray<float> CheckPerChargeValue;

	UPROPERTY(EditAnywhere, Category = Section)
	TArray<uint8> FuncCountPerAct;

	UPROPERTY(EditAnywhere, Category = Section)
	float FrameRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	EActType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	EActCycleType CycleType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	uint8 HasAnotherAct : 1;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cost)
	EActCostType CostType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cost)
	TArray<float> CostMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cost)
	TArray<float> CostStamina;

};
