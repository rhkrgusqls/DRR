// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/DRRActUnitBase.h"
#include "DRRShortShotActUnitProto2.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UDRRShortShotActUnitProto2 : public UDRRActUnitBase
{
	GENERATED_BODY()
public:
	UDRRShortShotActUnitProto2();

	virtual TArray<FOnActFuncDelegate> GetActFunc() override;



protected:
	virtual void BeginFunc(AActor* Owner) override;
	virtual void EndFunc(AActor* Owner) override;

private:
	void Func1(AActor* Owner);

};
