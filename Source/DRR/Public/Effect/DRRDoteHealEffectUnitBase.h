// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effect/DRREffectUnitBase.h"
#include "DRRDoteHealEffectUnitBase.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ADRRDoteHealEffectUnitBase : public ADRREffectUnitBase
{
	GENERATED_BODY()
public:

	virtual void UpdateFunc(AActor* target) override;
	
};
