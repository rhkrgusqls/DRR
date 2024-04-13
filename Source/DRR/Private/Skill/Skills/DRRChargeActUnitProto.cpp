// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRChargeActUnitProto.h"
#include "Skill/Skills/DRRTriggerActUnitProto.h"

#include "CharacterBase/CharacterBase.h"
#include "CharacterBase/DRRActComponent.h"

#include "Utilities/UtilityList.h"


UDRRChargeActUnitProto::UDRRChargeActUnitProto()
{
    
    ConstructorHelpers::FObjectFinder<UDA_ActData> DataAssetRef(TEXT("/Script/DRR.DA_ChargeActData'/Game/Blueprints/Weapon/Weapon3/DA_ChargeWeaponAct1.DA_ChargeWeaponAct1'"));
    if (DataAssetRef.Object)
    {
        ActData = DataAssetRef.Object;
    }

    
      
}

TArray<FOnActFuncDelegate> UDRRChargeActUnitProto::GetActFunc()
{
    TArray<FOnActFuncDelegate> arr;

    FOnActFuncDelegate temp;
    temp.BindUObject(this, &UDRRChargeActUnitProto::Func1);
    arr.Add(temp);
    temp.BindUObject(this, &UDRRChargeActUnitProto::Func2);
    arr.Add(temp);
    temp.BindUObject(this, &UDRRChargeActUnitProto::Func3);
    arr.Add(temp);
    return arr;
}

void UDRRChargeActUnitProto::BeginFunc(AActor* Owner)
{
}

void UDRRChargeActUnitProto::EndFunc(AActor* Owner)
{
    
}

bool UDRRChargeActUnitProto::IsAchieveCondition(AActor* Owner)
{

    return true;
}

void UDRRChargeActUnitProto::Func1(AActor* Owner)
{
    CLog::Log("ChargeFunc1");
}

void UDRRChargeActUnitProto::Func2(AActor* Owner)
{
    CLog::Log("ChargeFunc2");
}

void UDRRChargeActUnitProto::Func3(AActor* Owner)
{
    CLog::Log("ChargeFunc3");
}
