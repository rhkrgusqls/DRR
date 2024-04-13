// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRComboAct.h"
#include "Interface/DRRActableInterface.h"

UDRRComboAct::UDRRComboAct() :UDRRAct()
{

}


bool UDRRComboAct::BeginAct()
{

	curActCount = 0;
	curFuncCount = 0;
	return false;
}

bool UDRRComboAct::NextReset()
{
	return false;
}

FName UDRRComboAct::GetMontgeSectionName()
{

	FString CombineString = CurAct->MontageSectionPrefix + FString::FromInt(FMath::Clamp(curActCount+1,1,CurAct->MaxActCount));

	return FName(*CombineString);
}

void UDRRComboAct::EndAct()
{
	Super::EndAct();
}

bool UDRRComboAct::AfterAct()
{
	return true;
}
