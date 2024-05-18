// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRPlayerActUnitProto6.h"

#include "Skill/SkillElements/DRRPlayerMagicArrowProto.h"
#include "Utilities/UtilityList.h"
ADRRPlayerActUnitProto6::ADRRPlayerActUnitProto6()
{

	Loc=FVector(0.0f,0.0f,150.0f);
	LocRandomRadius = 15.0f;
	Rot = FRotator(-45.0f, 0.0f, 0.0f);
	RotRandomRange = 15.0f;
	ArrowShotDelay = 1.3f;
	ArrowCount = 6;
}

TArray<FOnActFuncDelegate> ADRRPlayerActUnitProto6::GetActFunc()
{
	TArray<FOnActFuncDelegate> arr;

	FOnActFuncDelegate temp;
	temp.BindUObject(this, &ADRRPlayerActUnitProto6::Func1);
	arr.Add(temp);
	return arr;
}

void ADRRPlayerActUnitProto6::BeginFunc(AActor* User)
{
}

void ADRRPlayerActUnitProto6::EndFunc(AActor* User)
{
}

void ADRRPlayerActUnitProto6::Func1(AActor* User)
{
	CLog::Log("ProjectileTest");
	for (int i = 0; i < ArrowCount; i++)
	{
		ADRRPlayerMagicArrowProto* Temp = GetWorld()->SpawnActor<ADRRPlayerMagicArrowProto>(Projectile, RandomArrowLocSet(User->GetActorLocation() + Loc, LocRandomRadius), RandomArrowRotSet(User->GetActorRotation() + Rot, RotRandomRange));
		Temp->Init(User, 15.0f);
		Temp->SetDelay(FMath::RandRange(ArrowShotDelay/2.0f, ArrowShotDelay));
	}
}

FVector ADRRPlayerActUnitProto6::RandomArrowLocSet(FVector Point, float RandomRadius)
{
	// 랜덤한 각도와 거리 생성
	float RandomAngle = FMath::RandRange(0.0f, 360.0f);
	float RandomDistance = FMath::RandRange(0.0f, RandomRadius);

	// 각도와 거리를 이용하여 새로운 위치 계산
	FVector Direction = FVector(FMath::Cos(FMath::DegreesToRadians(RandomAngle)), FMath::Sin(FMath::DegreesToRadians(RandomAngle)), 0.0f);
	FVector NewPosition = Point + Direction * RandomDistance;

	return NewPosition;
}

FRotator ADRRPlayerActUnitProto6::RandomArrowRotSet(FRotator Point, float RandomRange)
{
	float YawOffset = FMath::RandRange(-RandomRange, RandomRange);
	float PitchOffset = FMath::RandRange(-RandomRange, RandomRange);

	FRotator RandomRotator = FRotator(PitchOffset+Point.Pitch, YawOffset+Point.Yaw, Point.Roll);
	return RandomRotator;
}


