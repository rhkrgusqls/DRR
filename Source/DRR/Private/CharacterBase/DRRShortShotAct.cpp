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
	switch (CurAct->CycleType)
	{
	case EActCycleType::Reverse:
	case EActCycleType::Constant:
		return true;
		break;
	case EActCycleType::End:
	default:
		if (curActCount == CurAct->MaxActCount-1)
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	}
}
