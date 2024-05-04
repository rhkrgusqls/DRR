// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/DRRActUnitBase.h"
#include "Interface/DRRActableInterface.h"
#include "DRRCastActUnitProto.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ADRRCastActUnitProto : public ADRRActUnitBase
{
	GENERATED_BODY()
public:
	ADRRCastActUnitProto();

	virtual TArray<FOnActFuncDelegate> GetActFunc() override;
	virtual IDRRActableInterface* IsAchieveCondition(float Threshold) override;



protected:
	virtual void BeginFunc(AActor* User) override;
	virtual void EndFunc(AActor* User) override;

	
};
