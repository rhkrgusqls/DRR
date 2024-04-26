// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effect/DRREffectUnitBase.h"

class DRR_API DRREffect
{
public:
	DRREffect(class ADRREffectUnitBase* Effect);
	~DRREffect();
	void ExpireReset(class ADRREffectUnitBase* Effect);
public:
	void BeginEffect(AActor* Owner);
	void UseEffect(AActor* target);
	void EndEffect(AActor* Owner);
	void DelayReset();

	virtual void Tick(float DeltaTime);

	bool CheckExpire();
	bool CheckReadyToUse();
	class UDA_EffectData* GetEffectData() { return EffectActor->GetEffectData(); };
	AActor* GetUser() { return EffectActor->GetUser(); }
protected:
	TObjectPtr<class ADRREffectUnitBase> EffectActor;

	float CurDelay;
	float TimeRemain;
	uint8 UsageCount;
	


};
