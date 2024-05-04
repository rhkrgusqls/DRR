// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRCastActUnitProto.h"
#include "Skill/Skills/DRRTriggerActUnitProto.h"

#include "CharacterBase/CharacterBase.h"
#include "CharacterBase/DRRActComponent.h"
#include "Interface/DRRActableInterface.h"

#include "Utilities/UtilityList.h"

ADRRCastActUnitProto::ADRRCastActUnitProto()
{
    
    ConstructorHelpers::FObjectFinder<UDA_ActData> DataAssetRef(TEXT("/Script/DRR.DA_CastActData'/Game/Blueprints/Weapon/Weapon4/DA_CastWeaponAct1.DA_CastWeaponAct1'"));
    if (DataAssetRef.Object)
    {
        ActData = DataAssetRef.Object;
    }
}

TArray<FOnActFuncDelegate> ADRRCastActUnitProto::GetActFunc()
{
    return TArray<FOnActFuncDelegate>();
}

IDRRActableInterface* ADRRCastActUnitProto::IsAchieveCondition(float Threshold)
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


void ADRRCastActUnitProto::BeginFunc(AActor* User)
{
}

void ADRRCastActUnitProto::EndFunc(AActor* User)
{
}
