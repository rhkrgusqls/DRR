// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/BattleAct/DRRCastAct.h"
#include "Interface/DRRActableInterface.h"

DRRCastAct::DRRCastAct() :DRRAct()
{
}



bool DRRCastAct::BeginAct()
{
	curActCount = 0;
	curFuncCount = 0;

	return NextReset();
}

bool DRRCastAct::NextReset()
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

FName DRRCastAct::GetMontgeSectionName()
{
	FString CombineString = CurAct->MontageSectionPrefix;

	return FName(*CombineString);
}



bool DRRCastAct::AfterAct()
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
