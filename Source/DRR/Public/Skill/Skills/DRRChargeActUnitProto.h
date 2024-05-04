// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/DRRActUnitBase.h"
#include "Interface/DRRActableInterface.h"
#include "DRRChargeActUnitProto.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ADRRChargeActUnitProto : public ADRRActUnitBase
{
	GENERATED_BODY()

public:
	ADRRChargeActUnitProto();
	virtual TArray<FOnActFuncDelegate> GetActFunc() override;



protected:
	virtual void BeginFunc(AActor* User) override;
	virtual void EndFunc(AActor* User) override;
	virtual IDRRActableInterface* IsAchieveCondition(float Threshold) override;

private:
	void Func1(AActor* User);
	void Func2(AActor* User);
	void Func3(AActor* User);

protected:


};
