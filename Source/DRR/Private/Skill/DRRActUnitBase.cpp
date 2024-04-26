// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/DRRActUnitBase.h"
#include "DataAsset/Item/DA_WeaponData.h"
#include "DataAsset/DA_ActData.h"

// Sets default values
ADRRActUnitBase::ADRRActUnitBase()
{

}

TArray<FOnActFuncDelegate> ADRRActUnitBase::GetActFunc()
{
	return TArray<FOnActFuncDelegate>();
}

FOnActFuncDelegate ADRRActUnitBase::GetBeginActFunc()
{
	FOnActFuncDelegate Temp;

	Temp.BindUObject(this, &ADRRActUnitBase::BeginFunc);

	return Temp;

}

FOnActFuncDelegate ADRRActUnitBase::GetEndActFunc()
{
	FOnActFuncDelegate Temp;

	Temp.BindUObject(this, &ADRRActUnitBase::EndFunc);

	return Temp;
}

UDA_ActData* ADRRActUnitBase::GetActData()
{
	return ActData;
}

FOnActCheckConditionDelegate ADRRActUnitBase::GetAchieveCondition()
{
	FOnActCheckConditionDelegate Temp;
	
	Temp.BindUObject(this, &ADRRActUnitBase::IsAchieveCondition);
	return Temp;
}

void ADRRActUnitBase::BeginFunc(AActor* User)
{
}

void ADRRActUnitBase::EndFunc(AActor* User)
{

}

bool ADRRActUnitBase::IsAchieveCondition(AActor* User)
{
	return true;
}




