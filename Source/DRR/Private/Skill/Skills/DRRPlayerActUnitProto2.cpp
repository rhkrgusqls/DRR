// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRPlayerActUnitProto2.h"
#include "Skill/SkillElements/DRRPlayerProjectileProto.h"
#include "CharacterBase/CharacterBase.h"
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

	ACharacterBase* user = Cast< ACharacterBase>(User);
	const float defaultDamage = 5.0f;
	float damageResult = GetActData()->SkillCoefficient * defaultDamage * user->physicsAttack;

	Temp->Init(User, damageResult);
}
