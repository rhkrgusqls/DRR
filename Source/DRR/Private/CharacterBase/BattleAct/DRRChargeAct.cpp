// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/BattleAct/DRRChargeAct.h"
#include "Interface/DRRActableInterface.h"

DRRChargeAct::DRRChargeAct() :DRRAct()
{
}


void DRRChargeAct::ActRelease()
{
	AfterAct();
}

bool DRRChargeAct::BeginAct()
{
	curActCount = 0;
	curFuncCount = 0;
	return NextReset();
}

bool DRRChargeAct::NextReset()
{
	switch (CurAct->CycleType)
	{
	case EActCycleType::Reverse:
	case EActCycleType::Constant:
	case EActCycleType::End:
	default:
		return true;
		break;
	}


}

FName DRRChargeAct::GetMontgeSectionName()
{

	FString CombineString = CurAct->MontageSectionPrefix;
	return FName(*CombineString);
}




bool DRRChargeAct::AfterAct()
{
	return false;
}
