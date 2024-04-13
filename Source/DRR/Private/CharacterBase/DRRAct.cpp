// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRAct.h"
#include "Interface/DRRActableInterface.h"
#include "Utilities/UtilityList.h"

UDRRAct::UDRRAct()
{
	
}

void UDRRAct::SetActor(IDRRActableInterface* Target)
{
	SetActs(Target);
	CurAct = Target->GetActData();
	BeginAct();
}

void UDRRAct::ActRelease()
{

}

UDRRAct::~UDRRAct()
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

float UDRRAct::GetNextTime()
{
	return CurAct->EffectiveFrameCount[curActCount]/CurAct->FrameRate;
}

uint8 UDRRAct::NextAct()
{

	CLog::Log("UDRRAct::NextAct");
	curActCount = FMath::Clamp((curActCount + 1)%CurAct->MaxActCount, 0, CurAct->MaxActCount - 1);
	CLog::Log(curActCount);
	return curActCount;
}

bool UDRRAct::NextReset()
{
	return false;
}

uint8 UDRRAct::GetCurFuncCount()
{
	uint8 Temp = curFuncCount;
	curFuncCount=FMath::Clamp((curFuncCount+1)%ActFunc.Num(), 0, ActFunc.Num() - 1);
	
	return Temp;
}

FOnActFuncDelegate UDRRAct::DoBeginAct()
{
	
	return BeginActFunc;
	
}

FOnActFuncDelegate UDRRAct::DoAct()
{
	CLog::Log("UDRRAct::DoAct");
	return (ActFunc[GetCurFuncCount()]);
}

FOnActFuncDelegate UDRRAct::DoEndAct()
{
	return EndActFunc;
}

const UDA_ActData* UDRRAct::GetCurAct()
{
	return CurAct;
}

bool UDRRAct::BeginAct()
{

	curActCount = 0;
	curFuncCount = 0;
	return false;

}

FName UDRRAct::GetMontgeSectionName()
{
	return FName(TEXT("Default"));
}



void UDRRAct::EndAct()
{
	CLog::Log("EndAct");
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


bool UDRRAct::AfterAct()
{
	return true;
}

void UDRRAct::SetActs(IDRRActableInterface* Target)
{
	CLog::Log("UDRRAct::SetActs");
	BeginActFunc = Target->GetBeginActFunc();
	ActFunc = Target->GetActFunc( );
	EndActFunc = Target->GetEndActFunc();
	CLog::Log(ActFunc.Num());
	
	
}

void UDRRAct::BeginDestroy()
{
	Super::BeginDestroy();
	EndAct();

}
