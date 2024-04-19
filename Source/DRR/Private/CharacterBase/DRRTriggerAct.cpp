// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRTriggerAct.h"

DRRTriggerAct::DRRTriggerAct()
{
}

bool DRRTriggerAct::BeginAct()
{

	curActCount = 0;
	curFuncCount = 0;

	return NextReset();
}

bool DRRTriggerAct::NextReset()
{
	switch (CurAct->CycleType)
	{
	case EActCycleType::Reverse:
	case EActCycleType::Constant:
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

FName DRRTriggerAct::GetMontgeSectionName()
{

	FString CombineString = CurAct->MontageSectionPrefix + FString::FromInt(FMath::Clamp(curActCount + 1, 1, CurAct->MaxActCount));

	return FName(*CombineString);
}

bool DRRTriggerAct::AfterAct()
{switch (CurAct->CycleType)
	{
	case EActCycleType::Reverse:
	case EActCycleType::Constant:
	case EActCycleType::End:
	default:
		return false;
		break;
	}
}
