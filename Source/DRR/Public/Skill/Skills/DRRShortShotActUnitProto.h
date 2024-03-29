// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/DRRActUnitBase.h"
#include "DRRShortShotActUnitProto.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UDRRShortShotActUnitProto : public UDRRActUnitBase
{
	GENERATED_BODY()
public:
	UDRRShortShotActUnitProto();

	virtual TArray<FOnActFuncDelegate> GetActFunc() override;



protected:
	virtual void BeginFunc(AActor* Owner) override;
	virtual void EndFunc(AActor* Owner) override;

private:
	void Func1(AActor* Owner);

};
