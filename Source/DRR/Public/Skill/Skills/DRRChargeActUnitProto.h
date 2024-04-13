// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/DRRActUnitBase.h"
#include "DRRChargeActUnitProto.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UDRRChargeActUnitProto : public UDRRActUnitBase
{
	GENERATED_BODY()

public:
	UDRRChargeActUnitProto();
	virtual TArray<FOnActFuncDelegate> GetActFunc() override;



protected:
	virtual void BeginFunc(AActor* Owner) override;
	virtual void EndFunc(AActor* Owner) override;
	virtual bool IsAchieveCondition(AActor* Owner) override;

private:
	void Func1(AActor* Owner);
	void Func2(AActor* Owner);
	void Func3(AActor* Owner);

private:
};
