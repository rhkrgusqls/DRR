// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/DRRActUnitBase.h"
#include "DRRPlayerActUnitProto3.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ADRRPlayerActUnitProto3 : public ADRRActUnitBase
{
	GENERATED_BODY()

public:
	ADRRPlayerActUnitProto3();

	virtual TArray<FOnActFuncDelegate> GetActFunc() override;



protected:
	virtual void BeginFunc(AActor* User) override;
	virtual void EndFunc(AActor* User) override;

private:
	void Func1(AActor* User);
	void Func2(AActor* User);
	void Func3(AActor* User);

};
