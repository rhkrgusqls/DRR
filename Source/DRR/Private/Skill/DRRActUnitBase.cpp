// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/DRRActUnitBase.h"
#include "DataAsset/Item/DA_WeaponData.h"
#include "DataAsset/DA_ActData.h"

// Sets default values
UDRRActUnitBase::UDRRActUnitBase()
{

}

TArray<FOnActFuncDelegate> UDRRActUnitBase::GetActFunc()
{
	return TArray<FOnActFuncDelegate>();
}

FOnActFuncDelegate UDRRActUnitBase::GetBeginActFunc()
{
	FOnActFuncDelegate Temp;

	Temp.BindUObject(this, &UDRRActUnitBase::BeginFunc);

	return Temp;

}

FOnActFuncDelegate UDRRActUnitBase::GetEndActFunc()
{
	FOnActFuncDelegate Temp;

	Temp.BindUObject(this, &UDRRActUnitBase::EndFunc);

	return Temp;
}

UDA_ActData* UDRRActUnitBase::GetActData()
{
	return ActData;
}

FOnActCheckConditionDelegate UDRRActUnitBase::GetAchieveCondition()
{
	FOnActCheckConditionDelegate Temp;
	
	Temp.BindUObject(this, &UDRRActUnitBase::IsAchieveCondition);
	return Temp;
}

void UDRRActUnitBase::BeginFunc(AActor* Owner)
{
}

void UDRRActUnitBase::EndFunc(AActor* Owner)
{

}

bool UDRRActUnitBase::IsAchieveCondition(AActor* Owner)
{
	return true;
}




