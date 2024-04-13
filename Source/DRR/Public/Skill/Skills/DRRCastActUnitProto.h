// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/DRRActUnitBase.h"
#include "DRRCastActUnitProto.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UDRRCastActUnitProto : public UDRRActUnitBase
{
	GENERATED_BODY()
public:
	UDRRCastActUnitProto();

	virtual TArray<FOnActFuncDelegate> GetActFunc() override;



protected:
	virtual void BeginFunc(AActor* Owner) override;
	virtual void EndFunc(AActor* Owner) override;

	
};
