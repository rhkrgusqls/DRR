// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRShortShotActUnitProto2.h"

#include "Utilities/CLog.h"
ADRRShortShotActUnitProto2::ADRRShortShotActUnitProto2()
{
	ConstructorHelpers::FObjectFinder<UDA_ActData> DataAssetRef(TEXT("/Script/DRR.DA_ShortShotActData'/Game/Blueprints/Weapon/Weapon1/DA_ShortShotWeaponAct2.DA_ShortShotWeaponAct2'"));
	if (DataAssetRef.Object)
	{
		ActData = DataAssetRef.Object;
	}
	CLog::Log("ActDataCheck");
	CLog::Log(ActData != nullptr);
	CLog::Log(ActData->ActionName);
	
}

TArray<FOnActFuncDelegate> ADRRShortShotActUnitProto2::GetActFunc()
{
	TArray<FOnActFuncDelegate> arr;

	FOnActFuncDelegate temp;
	temp.BindUObject(this, &ADRRShortShotActUnitProto2::Func1);
	arr.Add(temp);
	return arr;
}

void ADRRShortShotActUnitProto2::BeginFunc(AActor* User)
{
	CLog::Log("ADRRShortShotActUnitProto2");
	CLog::Log("ActBeginFunc");
}

void ADRRShortShotActUnitProto2::EndFunc(AActor* User)
{
	CLog::Log("ActEndFunc");
}

void ADRRShortShotActUnitProto2::Func1(AActor* User)
{
	CLog::Log("ADRRShortShotActUnitProto2");
	CLog::Log("ActFunc1");

}
