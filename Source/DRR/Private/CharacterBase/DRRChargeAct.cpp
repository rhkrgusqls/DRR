// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRChargeAct.h"
#include "Interface/DRRActableInterface.h"

UDRRChargeAct::UDRRChargeAct() :UDRRAct()
{
}


void UDRRChargeAct::ActRelease()
{
	AfterAct();
}

bool UDRRChargeAct::BeginAct()
{
	return true;
}

bool UDRRChargeAct::NextReset()
{
	return true;
}

FName UDRRChargeAct::GetMontgeSectionName()
{
	FString CombineString = CurAct->MontageSectionPrefix + FString::FromInt(curActCount);

	return FName(*CombineString);
}



void UDRRChargeAct::EndAct()
{
}

bool UDRRChargeAct::AfterAct()
{
	return false;
}
