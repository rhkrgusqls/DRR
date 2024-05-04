// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRChargeActUnitProto.h"
#include "Skill/Skills/DRRTriggerActUnitProto.h"

#include "CharacterBase/CharacterBase.h"
#include "CharacterBase/DRRActComponent.h"
#include "Interface/DRRActableInterface.h"

#include "Utilities/UtilityList.h"


ADRRChargeActUnitProto::ADRRChargeActUnitProto()
{
    
    ConstructorHelpers::FObjectFinder<UDA_ActData> DataAssetRef(TEXT("/Script/DRR.DA_ChargeActData'/Game/Blueprints/Weapon/Weapon3/DA_ChargeWeaponAct1.DA_ChargeWeaponAct1'"));
    if (DataAssetRef.Object)
    {
        ActData = DataAssetRef.Object;
    }

    
      
}

TArray<FOnActFuncDelegate> ADRRChargeActUnitProto::GetActFunc()
{
    TArray<FOnActFuncDelegate> arr;

    FOnActFuncDelegate temp;
    temp.BindUObject(this, &ADRRChargeActUnitProto::Func1);
    arr.Add(temp);
    temp.BindUObject(this, &ADRRChargeActUnitProto::Func2);
    arr.Add(temp);
    temp.BindUObject(this, &ADRRChargeActUnitProto::Func3);
    arr.Add(temp);
    return arr;
}

void ADRRChargeActUnitProto::BeginFunc(AActor* User)
{
}

void ADRRChargeActUnitProto::EndFunc(AActor* User)
{
    
}

IDRRActableInterface* ADRRChargeActUnitProto::IsAchieveCondition(float Threshold)
{
    if (Threshold == 1.0f)
    {
        return CheckNextAct(0);
    }
    else
    {
        return nullptr;
    }
}


void ADRRChargeActUnitProto::Func1(AActor* User)
{
    CLog::Log("ChargeFunc1");
}

void ADRRChargeActUnitProto::Func2(AActor* User)
{
    CLog::Log("ChargeFunc2");
}

void ADRRChargeActUnitProto::Func3(AActor* User)
{
    CLog::Log("ChargeFunc3");
}
