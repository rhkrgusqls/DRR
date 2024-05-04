// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRPlayerActUnitProto2.h"
#include "Skill/SkillElements/DRRPlayerProjectileProto.h"
#include "Utilities/UtilityList.h"
ADRRPlayerActUnitProto2::ADRRPlayerActUnitProto2()
{
}

TArray<FOnActFuncDelegate> ADRRPlayerActUnitProto2::GetActFunc()
{
	TArray<FOnActFuncDelegate> arr;

	FOnActFuncDelegate temp;
	temp.BindUObject(this, &ADRRPlayerActUnitProto2::Func1);
	arr.Add(temp);
	return arr;
}

void ADRRPlayerActUnitProto2::BeginFunc(AActor* User)
{
}

void ADRRPlayerActUnitProto2::EndFunc(AActor* User)
{
}

void ADRRPlayerActUnitProto2::Func1(AActor* User)
{
	CLog::Log("ProjectileTest");
	ADRRPlayerProjectileProto* Temp= GetWorld()->SpawnActor<ADRRPlayerProjectileProto>(Projectile, User->GetActorLocation(), User->GetActorRotation());
	Temp->Init(User, 15.0f);
}
