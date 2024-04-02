// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRShortShotActUnitProto.h"

#include "Utilities/CLog.h"
UDRRShortShotActUnitProto::UDRRShortShotActUnitProto()
{
	ConstructorHelpers::FObjectFinder<UDA_ActData> DataAssetRef(TEXT("/Script/DRR.DA_ShortShotActData'/Game/Blueprints/Weapon/Weapon1/DA_ShortShotWeaponAct1.DA_ShortShotWeaponAct1'"));
	if (DataAssetRef.Object)
	{
		ActData = DataAssetRef.Object;
	}
	CLog::Log("ActDataCheck");
	CLog::Log(ActData != nullptr);
	CLog::Log(ActData->ActionName);
	
}

TArray<FOnActFuncDelegate> UDRRShortShotActUnitProto::GetActFunc()
{
	TArray<FOnActFuncDelegate> arr;

	FOnActFuncDelegate temp;
	temp.BindUObject(this, &UDRRShortShotActUnitProto::Func1);
	arr.Add(temp);
	return arr;
}

void UDRRShortShotActUnitProto::BeginFunc(AActor* Owner)
{
	CLog::Log("ActBeginFunc");
}

void UDRRShortShotActUnitProto::EndFunc(AActor* Owner)
{
	CLog::Log("ActEndFunc");
}

void UDRRShortShotActUnitProto::Func1(AActor* Owner)
{
	CLog::Log("ActFunc1");

}
