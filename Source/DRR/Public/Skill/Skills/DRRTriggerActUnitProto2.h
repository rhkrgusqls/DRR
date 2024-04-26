// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/DRRActUnitBase.h"
#include "DRRTriggerActUnitProto2.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ADRRTriggerActUnitProto2 : public ADRRActUnitBase
{
	GENERATED_BODY()
public:
	ADRRTriggerActUnitProto2();

	virtual TArray<FOnActFuncDelegate> GetActFunc() override;



protected:
	virtual void BeginFunc(AActor* User) override;
	virtual void EndFunc(AActor* User) override;

private:
	void Func1(AActor* User);
};
