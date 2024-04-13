// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRCastAct.h"
#include "Interface/DRRActableInterface.h"

UDRRCastAct::UDRRCastAct() :UDRRAct()
{
}



bool UDRRCastAct::BeginAct()
{
	return true;
}

bool UDRRCastAct::NextReset()
{
	return true;
}

FName UDRRCastAct::GetMontgeSectionName()
{
	FString CombineString = CurAct->MontageSectionPrefix + FString::FromInt(curActCount);

	return FName(*CombineString);
}


void UDRRCastAct::EndAct()
{
}

bool UDRRCastAct::AfterAct()
{
	return false;
}
