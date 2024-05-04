// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/BattleAct/DRRAct.h"
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
	
	for (FOnActFuncDelegate f : ActFunc)
	{
		f.Unbind();
	}
	ActFunc.Empty();
	Actor = nullptr;
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

void DRRAct::DoBeginAct(AActor* User)
{
	Actor->BeginFunc(User);
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

void DRRAct::DoEndAct(AActor* User)
{
	Actor->EndFunc(User);
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

	for (FOnActFuncDelegate f : ActFunc)
	{
		f.Unbind();
	}
	ActFunc.Empty();
	Actor = nullptr;

}

void DRRAct::IncreaseThreshold()
{
	if (GetCurAct()->HasAnotherAct)
	{
		threshold = GetCurAct()->CheckPerChargeValue[curActCount];
	}
}


bool DRRAct::AfterAct()
{
	return true;
}

void DRRAct::SetActs(IDRRActableInterface* Target)
{
	CLog::Log("DRRAct::SetActs");
	Actor = Target;
	ActFunc = Target->GetActFunc( );
	CLog::Log(ActFunc.Num());
	
	
}



bool DRRAct::IsLastNumAct()
{
	if ((curActCount + 1) < CurAct->MaxActCount)
		return false;
	else
		return true;
}

