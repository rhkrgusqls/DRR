// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRTriggerActUnitProto2.h"
#include "Utilities/UtilityList.h"

ADRRTriggerActUnitProto2::ADRRTriggerActUnitProto2()
{

	ConstructorHelpers::FObjectFinder<UDA_ActData> DataAssetRef(TEXT("/Script/DRR.DA_TriggerActData'/Game/Blueprints/Weapon/Weapon4/DA_CastWeaponTriggerAct.DA_CastWeaponTriggerAct'"));
	if (DataAssetRef.Object)
	{
		ActData = DataAssetRef.Object;
	}


}

TArray<FOnActFuncDelegate> ADRRTriggerActUnitProto2::GetActFunc()
{
	TArray<FOnActFuncDelegate> arr;

	FOnActFuncDelegate temp;
	temp.BindUObject(this, &ADRRTriggerActUnitProto2::Func1);
	arr.Add(temp);
	return arr;
}

void ADRRTriggerActUnitProto2::BeginFunc(AActor* User)
{

}

void ADRRTriggerActUnitProto2::EndFunc(AActor* User)
{

}

void ADRRTriggerActUnitProto2::Func1(AActor* User)
{
	CLog::Log("TriggerFunc");
}
