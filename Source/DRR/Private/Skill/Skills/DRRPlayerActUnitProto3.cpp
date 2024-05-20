// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRPlayerActUnitProto3.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Engine/DamageEvents.h"
#include "CharacterBase/CharacterBase.h"

#include "Utilities/CLog.h"
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


	ACharacterBase* UserChar = Cast<ACharacterBase>(User);

	UE_LOG(LogTemp, Log, TEXT("AttackHitCheck"));


	//충돌에 이름을 붙임,무시할 액터:this를 넣어 자신이 충돌되는걸 방지
	FCollisionQueryParams collisionParams(SCENE_QUERY_STAT(Attack), false, UserChar);

	FHitResult outHitResult;
	TArray<FHitResult> outHitResults;
	TArray<FOverlapResult> outOverlapResults;
	const float attackRange = 0;
	const float capsuleRadius = 150.0f;
	bool isHit;

	//액터의 현재 위치, 액터의 정면백터, 캡슐컴포넌트의 반지름크기
	const FVector start = UserChar->GetActorLocation()+capsuleRadius*UserChar->GetActorForwardVector();

	FVector end= UserChar->GetActorLocation() - capsuleRadius * UserChar->GetActorForwardVector();


	//캡슐의 중앙위치
	FVector capsulePosition = UserChar->GetActorLocation();

	float halfHeight = capsuleRadius;

	end = start + UserChar->GetActorForwardVector() * attackRange;
	isHit = GetWorld()->SweepSingleByChannel(outHitResult, start, end, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3, FCollisionShape::MakeSphere(capsuleRadius * 2), collisionParams);



	//DebugDraw
	bool isRemaining = false;
	FColor Color = isHit ? FColor::Green : FColor::Red;
	DrawDebugCapsule(GetWorld(), end, halfHeight, capsuleRadius * 2, FRotationMatrix::MakeFromZ(UserChar->GetActorForwardVector()).ToQuat(), Color, isRemaining, 3.0f);




	if (isHit)
	{

		FDamageEvent damageEvent;

		//충돌대상의 액터 가져와 피해를 입히는 함수 호출
		//언리얼에서 만들어둔 모든 액터들은 데미지를 입는다는 가정하에 만든함수
		//피해, 이벤트, 나의컨트롤러,가해자 액터
		ACharacterBase* Temp;
		if (outHitResult.GetActor())
		{
			Temp = Cast< ACharacterBase>(outHitResult.GetActor());
			if (Temp != nullptr)
			{

				const float defaultDamage = 10.0f;
				float damageResult = GetActData()->SkillCoefficient * defaultDamage * UserChar->physicsAttack;

				Temp->ReciveAttack(damageResult);


			}
		}
	}

	//드로우 디버그 가능한 상태일때만
	//디버그 용 코드를 출시할때 영향을 주지 않도록 테스트용 빌드에서만 작동하게함

}

void ADRRPlayerActUnitProto3::Func2(AActor* User)
{
	ACharacterBase* UserChar = Cast<ACharacterBase>(User);

	UE_LOG(LogTemp, Log, TEXT("AttackHitCheck"));


	//충돌에 이름을 붙임,무시할 액터:this를 넣어 자신이 충돌되는걸 방지
	FCollisionQueryParams collisionParams(SCENE_QUERY_STAT(Attack), false, UserChar);

	FHitResult outHitResult;
	TArray<FHitResult> outHitResults;
	TArray<FOverlapResult> outOverlapResults;
	const float attackRange = 0;
	const float capsuleRadius = 200.0f;
	bool isHit;

	//액터의 현재 위치, 액터의 정면백터, 캡슐컴포넌트의 반지름크기
	const FVector start = UserChar->GetActorLocation() + capsuleRadius * UserChar->GetActorForwardVector();

	FVector end = UserChar->GetActorLocation() - capsuleRadius * UserChar->GetActorForwardVector();


	//캡슐의 중앙위치
	FVector capsulePosition = UserChar->GetActorLocation();

	float halfHeight = capsuleRadius;

	end = start + UserChar->GetActorForwardVector() * attackRange;
	isHit = GetWorld()->SweepSingleByChannel(outHitResult, start, end, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3, FCollisionShape::MakeSphere(capsuleRadius * 2), collisionParams);



	//DebugDraw
	bool isRemaining = false;
	FColor Color = isHit ? FColor::Green : FColor::Red;
	DrawDebugCapsule(GetWorld(), end, halfHeight, capsuleRadius * 2, FRotationMatrix::MakeFromZ(UserChar->GetActorForwardVector()).ToQuat(), Color, isRemaining, 3.0f);




	if (isHit)
	{

		FDamageEvent damageEvent;

		//충돌대상의 액터 가져와 피해를 입히는 함수 호출
		//언리얼에서 만들어둔 모든 액터들은 데미지를 입는다는 가정하에 만든함수
		//피해, 이벤트, 나의컨트롤러,가해자 액터
		ACharacterBase* Temp;
		if (outHitResult.GetActor())
		{
			Temp = Cast< ACharacterBase>(outHitResult.GetActor());
			if (Temp != nullptr)
			{

				const float defaultDamage = 15.0f;
				float damageResult = GetActData()->SkillCoefficient * defaultDamage * UserChar->physicsAttack;

				Temp->ReciveAttack(damageResult);


			}
		}
	}

}

void ADRRPlayerActUnitProto3::Func3(AActor* User)
{
	ACharacterBase* UserChar = Cast<ACharacterBase>(User);

	UE_LOG(LogTemp, Log, TEXT("AttackHitCheck"));


	//충돌에 이름을 붙임,무시할 액터:this를 넣어 자신이 충돌되는걸 방지
	FCollisionQueryParams collisionParams(SCENE_QUERY_STAT(Attack), false, UserChar);

	FHitResult outHitResult;
	TArray<FHitResult> outHitResults;
	TArray<FOverlapResult> outOverlapResults;
	const float attackRange = 0;
	const float capsuleRadius = 250.0f;
	bool isHit;

	//액터의 현재 위치, 액터의 정면백터, 캡슐컴포넌트의 반지름크기
	const FVector start = UserChar->GetActorLocation() + capsuleRadius * UserChar->GetActorForwardVector();

	FVector end = UserChar->GetActorLocation() - capsuleRadius * UserChar->GetActorForwardVector();


	//캡슐의 중앙위치
	FVector capsulePosition = UserChar->GetActorLocation();

	float halfHeight = capsuleRadius;

	end = start + UserChar->GetActorForwardVector() * attackRange;
	isHit = GetWorld()->SweepSingleByChannel(outHitResult, start, end, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3, FCollisionShape::MakeSphere(capsuleRadius * 2), collisionParams);



	//DebugDraw
	bool isRemaining = false;
	FColor Color = isHit ? FColor::Green : FColor::Red;
	DrawDebugCapsule(GetWorld(), end, halfHeight, capsuleRadius * 2, FRotationMatrix::MakeFromZ(UserChar->GetActorForwardVector()).ToQuat(), Color, isRemaining, 3.0f);




	if (isHit)
	{

		FDamageEvent damageEvent;

		//충돌대상의 액터 가져와 피해를 입히는 함수 호출
		//언리얼에서 만들어둔 모든 액터들은 데미지를 입는다는 가정하에 만든함수
		//피해, 이벤트, 나의컨트롤러,가해자 액터
		ACharacterBase* Temp;
		if (outHitResult.GetActor())
		{
			Temp = Cast< ACharacterBase>(outHitResult.GetActor());
			if (Temp != nullptr)
			{

				const float defaultDamage = 20.0f;
				float damageResult = GetActData()->SkillCoefficient * defaultDamage * UserChar->physicsAttack;

				Temp->ReciveAttack(damageResult);


			}
		}
	}

}
