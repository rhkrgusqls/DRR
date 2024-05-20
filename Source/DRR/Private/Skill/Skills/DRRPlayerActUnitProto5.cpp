// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRPlayerActUnitProto5.h"
#include "Skill/SkillElements/DRRPlayerChainDiskProto.h"
#include "CharacterBase/CharacterBase.h"
#include "Utilities/UtilityList.h"
ADRRPlayerActUnitProto5::ADRRPlayerActUnitProto5()
{
}

TArray<FOnActFuncDelegate> ADRRPlayerActUnitProto5::GetActFunc()
{
	TArray<FOnActFuncDelegate> arr;

	FOnActFuncDelegate temp;
	temp.BindUObject(this, &ADRRPlayerActUnitProto5::Func1);
	arr.Add(temp);
	return arr;
}

void ADRRPlayerActUnitProto5::BeginFunc(AActor* User)
{
}

void ADRRPlayerActUnitProto5::EndFunc(AActor* User)
{
}

void ADRRPlayerActUnitProto5::Func1(AActor* User)
{
	CLog::Log("ProjectileTest");

	ACharacterBase* user = Cast< ACharacterBase>(User);
	const float defaultDamage = 3.5f;
	float damageResult = GetActData()->SkillCoefficient * defaultDamage * user->physicsAttack;

	ADRRPlayerChainDiskProto* Temp = GetWorld()->SpawnActor<ADRRPlayerChainDiskProto>(Projectile, User->GetActorLocation(), User->GetActorRotation());
	Temp->Init(User, damageResult);
}
