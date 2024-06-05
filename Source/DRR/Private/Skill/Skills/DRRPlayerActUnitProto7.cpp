// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRPlayerActUnitProto7.h"
#include "Skill/SkillElements/DRRPlayerMiniProjectileProto.h"
#include "CharacterBase/CharacterBase.h"
#include "Utilities/UtilityList.h"
ADRRPlayerActUnitProto7::ADRRPlayerActUnitProto7()
{
}

TArray<FOnActFuncDelegate> ADRRPlayerActUnitProto7::GetActFunc()
{
	TArray<FOnActFuncDelegate> arr;

	FOnActFuncDelegate temp;
	temp.BindUObject(this, &ADRRPlayerActUnitProto7::Func1);
	arr.Add(temp);
	return arr;
}

void ADRRPlayerActUnitProto7::BeginFunc(AActor* User)
{
}

void ADRRPlayerActUnitProto7::EndFunc(AActor* User)
{
}

void ADRRPlayerActUnitProto7::Func1(AActor* User)
{
	CLog::Log("ProjectileTest");

	ACharacterBase* user = Cast< ACharacterBase>(User);
	const float defaultDamage = 7.0f;
	float damageResult = GetActData()->SkillCoefficient * defaultDamage * user->physicsAttack;

	ADRRPlayerMiniProjectileProto* Temp = GetWorld()->SpawnActor<ADRRPlayerMiniProjectileProto>(Projectile, User->GetActorLocation(), User->GetActorRotation());
	Temp->Init(User, damageResult);
}


