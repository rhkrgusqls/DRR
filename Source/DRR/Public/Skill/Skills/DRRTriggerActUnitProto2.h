// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/DRRActUnitBase.h"
#include "DRRTriggerActUnitProto2.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UDRRTriggerActUnitProto2 : public UDRRActUnitBase
{
	GENERATED_BODY()
public:
	UDRRTriggerActUnitProto2();

	virtual TArray<FOnActFuncDelegate> GetActFunc() override;



protected:
	virtual void BeginFunc(AActor* Owner) override;
	virtual void EndFunc(AActor* Owner) override;

private:
	void Func1(AActor* Owner);
};
