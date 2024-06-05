// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRPlayerActUnitProto8.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Engine/DamageEvents.h"
#include "CharacterBase/CharacterBase.h"
#include "Skill/SkillElements/DRRPlayerStoneWallProto.h"

#include "Utilities/UtilityList.h"
ADRRPlayerActUnitProto8::ADRRPlayerActUnitProto8()
{
	Loc = FVector(200, 0, 0);
}

TArray<FOnActFuncDelegate> ADRRPlayerActUnitProto8::GetActFunc()
{

	TArray<FOnActFuncDelegate> arr;

	FOnActFuncDelegate temp;
	temp.BindUObject(this, &ADRRPlayerActUnitProto8::Func1);
	arr.Add(temp);
	return arr;
}

void ADRRPlayerActUnitProto8::BeginFunc(AActor* User)
{
}

void ADRRPlayerActUnitProto8::EndFunc(AActor* User)
{
}

void ADRRPlayerActUnitProto8::Func1(AActor* User)
{

	CLog::Log("DamageTestActFunc1");

	ACharacterBase* UserChar = Cast<ACharacterBase>(User);

	UE_LOG(LogTemp, Log, TEXT("AttackHitCheck"));



	float defaultDamage = 6.0f;
	float damageResult = defaultDamage * GetActData()->SkillCoefficient * UserChar->physicsAttack;



	CDisplayLog::Log(TEXT("Pillar"));

	ADRRPlayerStoneWallProto* Wall = GetWorld()->SpawnActor<ADRRPlayerStoneWallProto>(StoneWall, SetLocate(User, Loc), User->GetActorRotation());
	
	Wall->Init(User,damageResult);


	//��ο� ����� ������ �����϶���
	//����� �� �ڵ带 ����Ҷ� ������ ���� �ʵ��� �׽�Ʈ�� ���忡���� �۵��ϰ���


}

FVector ADRRPlayerActUnitProto8::SetLocate(AActor* User,FVector loc)
{
	FVector result;
	FVector x = User->GetActorForwardVector() * loc.X;
	FVector y = User->GetActorRightVector() * loc.Y;
	FVector z = FVector(0,0,loc.Z);
	result = User->GetActorLocation() + x+y+z;

	return result;
}

