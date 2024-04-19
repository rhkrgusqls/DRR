// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRCastActUnitProto.h"
#include "Skill/Skills/DRRTriggerActUnitProto.h"

#include "CharacterBase/CharacterBase.h"
#include "CharacterBase/DRRActComponent.h"

#include "Utilities/UtilityList.h"

UDRRCastActUnitProto::UDRRCastActUnitProto()
{
    
    ConstructorHelpers::FObjectFinder<UDA_ActData> DataAssetRef(TEXT("/Script/DRR.DA_CastActData'/Game/Blueprints/Weapon/Weapon4/DA_CastWeaponAct1.DA_CastWeaponAct1'"));
    if (DataAssetRef.Object)
    {
        ActData = DataAssetRef.Object;
    }
}

TArray<FOnActFuncDelegate> UDRRCastActUnitProto::GetActFunc()
{
    return TArray<FOnActFuncDelegate>();
}

bool UDRRCastActUnitProto::IsAchieveCondition(AActor* Owner)
{
    return true;
}

void UDRRCastActUnitProto::BeginFunc(AActor* Owner)
{
}

void UDRRCastActUnitProto::EndFunc(AActor* Owner)
{
}
