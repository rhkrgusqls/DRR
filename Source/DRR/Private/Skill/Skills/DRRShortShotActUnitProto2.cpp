// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRShortShotActUnitProto2.h"

#include "Utilities/CLog.h"
UDRRShortShotActUnitProto2::UDRRShortShotActUnitProto2()
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

TArray<FOnActFuncDelegate> UDRRShortShotActUnitProto2::GetActFunc()
{
	TArray<FOnActFuncDelegate> arr;

	FOnActFuncDelegate temp;
	temp.BindUObject(this, &UDRRShortShotActUnitProto2::Func1);
	arr.Add(temp);
	return arr;
}

void UDRRShortShotActUnitProto2::BeginFunc(AActor* Owner)
{
	CLog::Log("UDRRShortShotActUnitProto2");
	CLog::Log("ActBeginFunc");
}

void UDRRShortShotActUnitProto2::EndFunc(AActor* Owner)
{
	CLog::Log("ActEndFunc");
}

void UDRRShortShotActUnitProto2::Func1(AActor* Owner)
{
	CLog::Log("UDRRShortShotActUnitProto2");
	CLog::Log("ActFunc1");

}
