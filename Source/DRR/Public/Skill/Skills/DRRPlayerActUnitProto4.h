// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/DRRActUnitBase.h"
#include "DRRPlayerActUnitProto4.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ADRRPlayerActUnitProto4 : public ADRRActUnitBase
{
	GENERATED_BODY()

public:
	ADRRPlayerActUnitProto4();

	virtual TArray<FOnActFuncDelegate> GetActFunc() override;



protected:
	virtual void BeginFunc(AActor* User) override;
	virtual void EndFunc(AActor* User) override;

private:
	void Func1(AActor* User);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	TSubclassOf<class ADRRPlayerStonePillarProto> StonePillar;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackRange)
	float AttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackRange)
	float AttackRadius;

};
