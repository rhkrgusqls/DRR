// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRCastAct.h"
#include "Interface/DRRActableInterface.h"

UDRRCastAct::UDRRCastAct() :UDRRAct()
{
}



bool UDRRCastAct::BeginAct()
{
	return NextReset();
}

bool UDRRCastAct::NextReset()
{
	if (curActCount + 1 < GetCurAct()->MaxActCount)
	{
		return true;
	}
	else
	{

		return false;
	}
}

FName UDRRCastAct::GetMontgeSectionName()
{
	FString CombineString = CurAct->MontageSectionPrefix;

	return FName(*CombineString);
}


void UDRRCastAct::EndAct()
{
	Super::EndAct();
}

bool UDRRCastAct::AfterAct()
{
	return false;
}
