// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRTriggerActUnitProto.h"
#include "Utilities/UtilityList.h"

UDRRTriggerActUnitProto::UDRRTriggerActUnitProto()
{

	ConstructorHelpers::FObjectFinder<UDA_ActData> DataAssetRef(TEXT("/Script/DRR.DA_TriggerActData'/Game/Blueprints/Weapon/Weapon3/DA_ChargeWeaponTriggerAct.DA_ChargeWeaponTriggerAct'"));
	if (DataAssetRef.Object)
	{
		ActData = DataAssetRef.Object;
	}


}

TArray<FOnActFuncDelegate> UDRRTriggerActUnitProto::GetActFunc()
{
	TArray<FOnActFuncDelegate> arr;

	FOnActFuncDelegate temp;
	temp.BindUObject(this, &UDRRTriggerActUnitProto::Func1);
	arr.Add(temp);
	return arr;
}

void UDRRTriggerActUnitProto::BeginFunc(AActor* Owner)
{

}

void UDRRTriggerActUnitProto::EndFunc(AActor* Owner)
{

}

void UDRRTriggerActUnitProto::Func1(AActor* Owner)
{
	CLog::Log("TriggerFunc");
}
