// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRComboAct.h"
#include "Interface/DRRActableInterface.h"

DRRComboAct::DRRComboAct() :DRRAct()
{

}


bool DRRComboAct::BeginAct()
{

	curActCount = 0;
	curFuncCount = 0;
	return NextReset();
}

bool DRRComboAct::NextReset()
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
}

FName DRRComboAct::GetMontgeSectionName()
{

	FString CombineString = CurAct->MontageSectionPrefix + FString::FromInt(FMath::Clamp(curActCount+1,1,CurAct->MaxActCount));

	return FName(*CombineString);
}


bool DRRComboAct::AfterAct()
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
