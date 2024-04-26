// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/Effect/DRREffect.h"
#include "Effect/DRREffectUnitBase.h"
#include "DataAsset/DA_EffectData.h"

DRREffect::DRREffect(class ADRREffectUnitBase* Effect)
{
	EffectActor = Effect;

	CurDelay=0.0f;
	TimeRemain = EffectActor->GetEffectData()->PassiveDuration;
	UsageCount= EffectActor->GetEffectData()->UsageCount;
	
}

DRREffect::~DRREffect()
{
}

void DRREffect::ExpireReset(class ADRREffectUnitBase* Effect)
{

	TimeRemain = EffectActor->GetEffectData()->PassiveDuration;
	UsageCount = EffectActor->GetEffectData()->UsageCount;
}

void DRREffect::BeginEffect(AActor* Owner)
{
	EffectActor->SetTarget(Owner);
	EffectActor->BeginFunc(Owner);

}

void DRREffect::EndEffect(AActor* Owner)
{
	EffectActor->EndFunc(Owner);
	EffectActor->RemoveEffect();
	delete(this);
}

void DRREffect::DelayReset()
{
	CurDelay=GetEffectData()->PassiveDelay;
	UsageCount--;
}


void DRREffect::UseEffect(AActor* target)
{
	EffectActor->UpdateFunc(target);
}


void DRREffect::Tick(float DeltaTime)
{

	CurDelay=FMath::Max(0,CurDelay-DeltaTime);
	TimeRemain = FMath::Max(0, TimeRemain - DeltaTime);
}

bool DRREffect::CheckExpire()
{
	switch (EffectActor->GetEffectData()->ExpirationType)
	{
	case EExpirationType::Duration:
		if ( TimeRemain == 0.0f)
			return true;
		break;
	case EExpirationType::Usage:
		if (UsageCount == 0 )
			return true;
		break;
	case EExpirationType::DurationOrUse:
		if (UsageCount == 0 || TimeRemain == 0.0f)
			return true;
		break;
	case EExpirationType::Permanent:
	default:
		break;

	}
	return false;
}

bool DRREffect::CheckReadyToUse()
{
	return CurDelay == 0.0f ? true : false;
}
