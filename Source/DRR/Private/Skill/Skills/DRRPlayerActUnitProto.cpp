// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRPlayerActUnitProto.h"

#include "Utilities/CLog.h"
UDRRPlayerActUnitProto::UDRRPlayerActUnitProto()
{
	ConstructorHelpers::FObjectFinder<UDA_ActData> DataAssetRef(TEXT("/Script/DRR.DA_ShortShotActData'/Game/Blueprints/Weapon/PlayerTestWeapon/DA_PlayerWeaponProtoAct1.DA_PlayerWeaponProtoAct1'"));
	if (DataAssetRef.Object)
	{
		ActData = DataAssetRef.Object;
	}
	CLog::Log("ActDataCheck");
	CLog::Log(ActData != nullptr);
	CLog::Log(ActData->ActionName);
	
}

TArray<FOnActFuncDelegate> UDRRPlayerActUnitProto::GetActFunc()
{
	TArray<FOnActFuncDelegate> arr;

	FOnActFuncDelegate temp;
	temp.BindUObject(this, &UDRRPlayerActUnitProto::Func1);
	arr.Add(temp);
	return arr;
}

void UDRRPlayerActUnitProto::BeginFunc(AActor* Owner)
{
	CLog::Log("ActBeginFunc");
}

void UDRRPlayerActUnitProto::EndFunc(AActor* Owner)
{
	CLog::Log("ActEndFunc");
}

void UDRRPlayerActUnitProto::Func1(AActor* Owner)
{
	CLog::Log("ActFunc1");

}
