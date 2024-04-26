// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRComboActUnitProto.h"
#include "Utilities/CLog.h"

ADRRComboActUnitProto::ADRRComboActUnitProto()
{
	ConstructorHelpers::FObjectFinder<UDA_ActData> DataAssetRef(TEXT("/Script/DRR.DA_ComboActData'/Game/Blueprints/Weapon/Weapon2/DA_ComboWeaponAct1.DA_ComboWeaponAct1'"));
	if (DataAssetRef.Object)
	{
		ActData = DataAssetRef.Object;
	}
	CLog::Log("ActDataCheck");
	CLog::Log(ActData != nullptr);
}

TArray<FOnActFuncDelegate> ADRRComboActUnitProto::GetActFunc()
{

	TArray<FOnActFuncDelegate> arr;

	
	FOnActFuncDelegate temp;
	temp.BindUObject(this, &ADRRComboActUnitProto::Func1);
	arr.Add(temp);
	temp.BindUObject(this, &ADRRComboActUnitProto::Func2);
	arr.Add(temp);
	temp.BindUObject(this, &ADRRComboActUnitProto::Func3);
	arr.Add(temp);
	return arr;
}

void ADRRComboActUnitProto::BeginFunc(AActor* User)
{
	CLog::Log("ActBeginFunc");
}

void ADRRComboActUnitProto::EndFunc(AActor* User)
{
	CLog::Log("ActEndFunc");
}

void ADRRComboActUnitProto::Func1(AActor* User)
{
	CLog::Log("ComboFunc1");
}

void ADRRComboActUnitProto::Func2(AActor* User)
{
	CLog::Log("ComboFunc2");
}

void ADRRComboActUnitProto::Func3(AActor* User)
{
	CLog::Log("ComboFunc3");
}
