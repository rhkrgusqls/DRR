// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/DRRActUnitBase.h"
#include "DataAsset/Item/DA_WeaponData.h"
#include "Interface/DRRActableInterface.h"
#include "DataAsset/DA_ActData.h"

// Sets default values
ADRRActUnitBase::ADRRActUnitBase()
{

}

TArray<FOnActFuncDelegate> ADRRActUnitBase::GetActFunc()
{
	return TArray<FOnActFuncDelegate>();
}


UDA_ActData* ADRRActUnitBase::GetActData()
{
	return ActData;
}

void ADRRActUnitBase::BeginFunc(AActor* User)
{
}

void ADRRActUnitBase::EndFunc(AActor* User)
{

}

IDRRActableInterface* ADRRActUnitBase::IsAchieveCondition(float Threshold)
{
	return nullptr;
}

void ADRRActUnitBase::ActDestroy()
{

	GetWorld()->GetTimerManager().SetTimer(ExpireHandle, this, &ADRRActUnitBase::Expire, 5.0f, false);
}

void ADRRActUnitBase::Expire()
{
	Destroy();
}

void ADRRActUnitBase::BeginPlay()
{
	Super::BeginPlay();
	for (auto i : NextActClass)
	{
		ADRRActUnitBase* Temp = GetWorld()->SpawnActor<ADRRActUnitBase>(i);
		if (Temp)
		{
			NextActUnit.Add(Temp);
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, false);
			Temp->AttachToActor(this, AttachmentRules);

		}
		
	}
}

IDRRActableInterface* ADRRActUnitBase::CheckNextAct(uint8 num)
{
	if (NextActUnit.Num() > num)
	{
		return NextActUnit[num];
	}
	else
	{

		return nullptr;
	}
}





