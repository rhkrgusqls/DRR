// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRShortShotAct.h"
#include "Interface/DRRActableInterface.h"

UDRRShortShotAct::UDRRShortShotAct() :UDRRAct()
{
    
}


bool UDRRShortShotAct::BeginAct()
{
    
    curActCount = 0;
    curFuncCount = 0;
    return false;
}

bool UDRRShortShotAct::NextReset()
{
    return false;
}
float UDRRShortShotAct::GetNextTime()
{
    return CurAct->EffectiveFrameCount[0] / CurAct->FrameRate;
}




void UDRRShortShotAct::EndAct()
{

    Super::EndAct();

}

bool UDRRShortShotAct::AfterAct()
{
    return true;
}
