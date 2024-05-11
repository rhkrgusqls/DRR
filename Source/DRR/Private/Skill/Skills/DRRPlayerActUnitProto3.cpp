// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRPlayerActUnitProto3.h"

ADRRPlayerActUnitProto3::ADRRPlayerActUnitProto3()
{
}

TArray<FOnActFuncDelegate> ADRRPlayerActUnitProto3::GetActFunc()
{
	TArray<FOnActFuncDelegate> arr;

	FOnActFuncDelegate temp;
	temp.BindUObject(this, &ADRRPlayerActUnitProto3::Func1);
	arr.Add(temp);
	temp.BindUObject(this, &ADRRPlayerActUnitProto3::Func2);
	arr.Add(temp);
	temp.BindUObject(this, &ADRRPlayerActUnitProto3::Func3);
	arr.Add(temp);
	return arr;
}

void ADRRPlayerActUnitProto3::BeginFunc(AActor* User)
{
}

void ADRRPlayerActUnitProto3::EndFunc(AActor* User)
{
}

void ADRRPlayerActUnitProto3::Func1(AActor* User)
{
}

void ADRRPlayerActUnitProto3::Func2(AActor* User)
{
}

void ADRRPlayerActUnitProto3::Func3(AActor* User)
{
}
