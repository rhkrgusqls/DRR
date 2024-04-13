// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRTriggerAct.h"

UDRRTriggerAct::UDRRTriggerAct()
{
}

bool UDRRTriggerAct::BeginAct()
{

	curActCount = 0;
	curFuncCount = 0;
	return false; 
}

bool UDRRTriggerAct::NextReset()
{
	return true;
}

FName UDRRTriggerAct::GetMontgeSectionName()
{

	FString CombineString = CurAct->MontageSectionPrefix + FString::FromInt(FMath::Clamp(curActCount + 1, 1, CurAct->MaxActCount));

	return FName(*CombineString);
}

void UDRRTriggerAct::EndAct()
{
	Super::EndAct();
}

bool UDRRTriggerAct::AfterAct()
{
	return false;
}
