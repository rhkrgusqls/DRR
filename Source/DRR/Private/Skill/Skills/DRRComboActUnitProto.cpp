// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRComboActUnitProto.h"
#include "Utilities/CLog.h"

UDRRComboActUnitProto::UDRRComboActUnitProto()
{
	ConstructorHelpers::FObjectFinder<UDA_ActData> DataAssetRef(TEXT("/Script/DRR.DA_ComboActData'/Game/Blueprints/Weapon/Weapon2/DA_ComboWeaponAct1.DA_ComboWeaponAct1'"));
	if (DataAssetRef.Object)
	{
		ActData = DataAssetRef.Object;
	}
	CLog::Log("ActDataCheck");
	CLog::Log(ActData != nullptr);
}

TArray<FOnActFuncDelegate> UDRRComboActUnitProto::GetActFunc()
{

	TArray<FOnActFuncDelegate> arr;

	
	FOnActFuncDelegate temp;
	temp.BindUObject(this, &UDRRComboActUnitProto::Func1);
	arr.Add(temp);
	temp.BindUObject(this, &UDRRComboActUnitProto::Func2);
	arr.Add(temp);
	temp.BindUObject(this, &UDRRComboActUnitProto::Func3);
	arr.Add(temp);
	return arr;
}

void UDRRComboActUnitProto::BeginFunc(AActor* Owner)
{
	CLog::Log("ActBeginFunc");
}

void UDRRComboActUnitProto::EndFunc(AActor* Owner)
{
	CLog::Log("ActEndFunc");
}

void UDRRComboActUnitProto::Func1(AActor* Owner)
{
	CLog::Log("ComboFunc1");
}

void UDRRComboActUnitProto::Func2(AActor* Owner)
{
	CLog::Log("ComboFunc2");
}

void UDRRComboActUnitProto::Func3(AActor* Owner)
{
	CLog::Log("ComboFunc3");
}
