// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/DRRActUnitBase.h"
#include "DRRPlayerActUnitProto6.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ADRRPlayerActUnitProto6 : public ADRRActUnitBase
{
	GENERATED_BODY()
public:
	ADRRPlayerActUnitProto6();

	virtual TArray<FOnActFuncDelegate> GetActFunc() override;



protected:
	virtual void BeginFunc(AActor* User) override;
	virtual void EndFunc(AActor* User) override;

private:
	void Func1(AActor* User);
	FVector RandomArrowLocSet(FVector Point,float RandomRadius);
	FRotator RandomArrowRotSet(FRotator Point,float RandomRange);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	TSubclassOf<class ADRRPlayerMagicArrowProto> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RandomSetting)
	uint8 ArrowCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RandomSetting)
	float ArrowShotDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RandomSetting)
	FVector Loc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RandomSetting)
	float LocRandomRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RandomSetting)
	FRotator Rot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RandomSetting)
	float RotRandomRange;


};
