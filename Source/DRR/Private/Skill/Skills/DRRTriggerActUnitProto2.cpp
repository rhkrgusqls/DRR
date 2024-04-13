// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRTriggerActUnitProto2.h"
#include "Utilities/UtilityList.h"

UDRRTriggerActUnitProto2::UDRRTriggerActUnitProto2()
{

	ConstructorHelpers::FObjectFinder<UDA_ActData> DataAssetRef(TEXT("/Script/DRR.DA_TriggerActData'/Game/Blueprints/Weapon/Weapon4/DA_CastWeaponTriggerAct.DA_CastWeaponTriggerAct'"));
	if (DataAssetRef.Object)
	{
		ActData = DataAssetRef.Object;
	}


}

TArray<FOnActFuncDelegate> UDRRTriggerActUnitProto2::GetActFunc()
{
	TArray<FOnActFuncDelegate> arr;

	FOnActFuncDelegate temp;
	temp.BindUObject(this, &UDRRTriggerActUnitProto2::Func1);
	arr.Add(temp);
	return arr;
}

void UDRRTriggerActUnitProto2::BeginFunc(AActor* Owner)
{

}

void UDRRTriggerActUnitProto2::EndFunc(AActor* Owner)
{

}

void UDRRTriggerActUnitProto2::Func1(AActor* Owner)
{
	CLog::Log("TriggerFunc");
}
