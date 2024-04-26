// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRTriggerActUnitProto.h"
#include "Utilities/UtilityList.h"

ADRRTriggerActUnitProto::ADRRTriggerActUnitProto()
{

	ConstructorHelpers::FObjectFinder<UDA_ActData> DataAssetRef(TEXT("/Script/DRR.DA_TriggerActData'/Game/Blueprints/Weapon/Weapon3/DA_ChargeWeaponTriggerAct.DA_ChargeWeaponTriggerAct'"));
	if (DataAssetRef.Object)
	{
		ActData = DataAssetRef.Object;
	}


}

TArray<FOnActFuncDelegate> ADRRTriggerActUnitProto::GetActFunc()
{
	TArray<FOnActFuncDelegate> arr;

	FOnActFuncDelegate temp;
	temp.BindUObject(this, &ADRRTriggerActUnitProto::Func1);
	arr.Add(temp);
	return arr;
}

void ADRRTriggerActUnitProto::BeginFunc(AActor* User)
{

}

void ADRRTriggerActUnitProto::EndFunc(AActor* User)
{

}

void ADRRTriggerActUnitProto::Func1(AActor* User)
{
	CLog::Log("TriggerFunc");
}
