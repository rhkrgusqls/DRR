// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRAct.h"
#include "Interface/DRRActableInterface.h"
#include "Utilities/UtilityList.h"

DRRAct::DRRAct()
{
	
}

void DRRAct::SetActor(IDRRActableInterface* Target)
{
	SetActs(Target);
	CurAct = Target->GetActData();
	BeginAct();
}

void DRRAct::ActRelease()
{

}

DRRAct::~DRRAct()
{
	if (BeginActFunc.IsBound())
	{
		BeginActFunc.Unbind();

	}
	if (BeginActFunc.IsBound())
	{
		EndActFunc.Unbind();

	}
	for (FOnActFuncDelegate f : ActFunc)
	{
		f.Unbind();
	}
	ActFunc.Empty();
}

float DRRAct::GetNextTime()
{
	return CurAct->EffectiveFrameCount[curActCount]/CurAct->FrameRate;
}

uint8 DRRAct::NextAct()
{

	CLog::Log("DRRAct::NextAct");
	switch (CurAct->CycleType)
	{
	case EActCycleType::Reverse :
		curActCount = FMath::Clamp((curActCount + 1) % CurAct->MaxActCount, 0, CurAct->MaxActCount - 1);
		break;
	case EActCycleType::Constant :
	case EActCycleType::End :
	default :
		curActCount = FMath::Clamp((curActCount + 1), 0, CurAct->MaxActCount - 1);

		break;
	}
	CLog::Log(curActCount);
	curFuncCount = 0;
	return curActCount;
}

bool DRRAct::NextReset()
{
	
	return false;
}

uint8 DRRAct::GetCurFuncCount()
{
	uint8 Temp = curFuncCount;
	curFuncCount=FMath::Clamp((curFuncCount+1)%ActFunc.Num(), 0, ActFunc.Num() - 1);
	
	return Temp;
}

FOnActFuncDelegate DRRAct::DoBeginAct()
{
	
	return BeginActFunc;
	
}

FOnActFuncDelegate DRRAct::DoAct()
{
	CLog::Log("DRRAct::DoAct");
	uint8 Result = 0;
	for (int i = 0; i < curActCount; i++)
	{
		Result += CurAct->FuncCountPerAct[i];
	}
	Result += curFuncCount;
	curFuncCount++;
	return (ActFunc[Result]);
}

FOnActFuncDelegate DRRAct::DoEndAct()
{


	return EndActFunc;
}

const UDA_ActData* DRRAct::GetCurAct()
{
	return CurAct;
}

bool DRRAct::BeginAct()
{

	curActCount = 0;
	curFuncCount = 0;
	return false;

}

FName DRRAct::GetMontgeSectionName()
{
	FString CombineString = CurAct->MontageSectionPrefix;
	return FName(*CombineString);
}



void DRRAct::EndAct()
{
	CLog::Log("DRRAct::EndAct");
	if (BeginActFunc.IsBound())
	{
		BeginActFunc.Unbind();

	}
	if (BeginActFunc.IsBound())
	{
		EndActFunc.Unbind();

	}
	for (FOnActFuncDelegate f : ActFunc)
	{
		f.Unbind();
	}
	ActFunc.Empty();
	

}


bool DRRAct::AfterAct()
{
	return true;
}

void DRRAct::SetActs(IDRRActableInterface* Target)
{
	CLog::Log("DRRAct::SetActs");
	BeginActFunc = Target->GetBeginActFunc();
	ActFunc = Target->GetActFunc( );
	EndActFunc = Target->GetEndActFunc();
	ConditionCheckFunc = Target->GetAchieveCondition();
	CLog::Log(ActFunc.Num());
	CLog::Log("NextActBound");
	CLog::Log(ConditionCheckFunc.IsBound() == true);
	
	
}

bool DRRAct::IsLastNumAct()
{
	if ((curActCount + 1) < CurAct->MaxActCount)
		return false;
	else
		return true;
}

