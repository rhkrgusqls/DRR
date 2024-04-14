// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRShortShotAct.h"
#include "Interface/DRRActableInterface.h"

DRRShortShotAct::DRRShortShotAct() :DRRAct()
{
    
}


bool DRRShortShotAct::BeginAct()
{
    
    curActCount = 0;
    curFuncCount = 0;
    return false;
}

bool DRRShortShotAct::NextReset()
{
	switch (CurAct->CycleType)
	{
	case EActCycleType::Reverse:
	case EActCycleType::Constant:
	case EActCycleType::End:
	default:
		return false;
		break;
	}

	return false;
}
float DRRShortShotAct::GetNextTime()
{
    return CurAct->EffectiveFrameCount[0] / CurAct->FrameRate;
}




bool DRRShortShotAct::AfterAct()
{
	switch (CurAct->CycleType)
	{
	case EActCycleType::Reverse:
	case EActCycleType::Constant:
		return true;
		break;
	case EActCycleType::End:
	default:
		if (IsLastNumAct())
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
