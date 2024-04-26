// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CharacterBase/Effect/DRREffect.h"

/**
 * 
 */
class DRR_API DRROnDamageEffect : public DRREffect
{
public:
	DRROnDamageEffect(class ADRREffectUnitBase* Effect);
	~DRROnDamageEffect();
};
