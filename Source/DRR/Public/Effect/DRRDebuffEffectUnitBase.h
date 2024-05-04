// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effect/DRREffectUnitBase.h"
#include "DRRDebuffEffectUnitBase.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ADRRDebuffEffectUnitBase : public ADRREffectUnitBase
{
	GENERATED_BODY()

public:
	virtual void BeginFunc(AActor* target) override;
	virtual void EndFunc(AActor* target) override;

protected:
	void AddStatus(AActor* target, float Mul);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EffectData)
	TObjectPtr<class UDA_StatusData> StatusData;

};
