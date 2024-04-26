// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/DRRActUnitBase.h"
#include "DRRShortShotActUnitProto2.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ADRRShortShotActUnitProto2 : public ADRRActUnitBase
{
	GENERATED_BODY()
public:
	ADRRShortShotActUnitProto2();

	virtual TArray<FOnActFuncDelegate> GetActFunc() override;



protected:
	virtual void BeginFunc(AActor* User) override;
	virtual void EndFunc(AActor* User) override;

private:
	void Func1(AActor* User);

};
