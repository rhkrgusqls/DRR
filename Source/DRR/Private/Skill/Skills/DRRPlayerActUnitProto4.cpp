// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRPlayerActUnitProto4.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Engine/DamageEvents.h"
#include "CharacterBase/CharacterBase.h"
#include "Skill/SkillElements/DRRPlayerStonePillarProto.h"

#include "Utilities/UtilityList.h"
ADRRPlayerActUnitProto4::ADRRPlayerActUnitProto4()
{
}

TArray<FOnActFuncDelegate> ADRRPlayerActUnitProto4::GetActFunc()
{

	TArray<FOnActFuncDelegate> arr;

	FOnActFuncDelegate temp;
	temp.BindUObject(this, &ADRRPlayerActUnitProto4::Func1);
	arr.Add(temp);
	return arr;
}

void ADRRPlayerActUnitProto4::BeginFunc(AActor* User)
{
}

void ADRRPlayerActUnitProto4::EndFunc(AActor* User)
{
}

void ADRRPlayerActUnitProto4::Func1(AActor* User)
{

	CLog::Log("DamageTestActFunc1");

	ACharacterBase* UserChar = Cast<ACharacterBase>(User);

	UE_LOG(LogTemp, Log, TEXT("AttackHitCheck"));


	//충돌에 이름을 붙임,무시할 액터:this를 넣어 자신이 충돌되는걸 방지
	FCollisionQueryParams collisionParams(SCENE_QUERY_STAT(Attack), false, UserChar);

	FHitResult outHitResult;
	TArray<FHitResult> outHitResults;
	TArray<FOverlapResult> outOverlapResults;
	const float attackRange = 600.0f;
	const float capsuleRadius = 200.0f;
	bool isHit;

	//액터의 현재 위치, 액터의 정면백터, 캡슐컴포넌트의 반지름크기
	const FVector start = UserChar->GetActorLocation() + UserChar->GetActorForwardVector() * UserChar->GetCapsuleComponent()->GetScaledCapsuleRadius();

	FVector end;


	//캡슐의 중앙위치
	FVector capsulePosition = start + (end - start) / 2.0f;

	float halfHeight = attackRange / 2.0f;

	end = start + UserChar->GetActorForwardVector() * attackRange;
	isHit = GetWorld()->SweepMultiByChannel(outHitResults, start, end, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3, FCollisionShape::MakeSphere(capsuleRadius * 2), collisionParams);



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

		for (auto i : outHitResults)
		{
			ACharacterBase* Temp;
			if (i.GetActor())
			{
				Temp = Cast< ACharacterBase>(i.GetActor());
				if (Temp != nullptr)
				{
					float damageResult = GetActData()->SkillCoefficient * UserChar->physicsAttack;



					CDisplayLog::Log(TEXT("Pillar"));

					ADRRPlayerStonePillarProto* Pillar = GetWorld()->SpawnActor<ADRRPlayerStonePillarProto>(StonePillar, Temp->GetActorLocation(), Temp->GetActorRotation());
					Pillar->Init(User, damageResult);


				}
			}
		}

		
	}

	//드로우 디버그 가능한 상태일때만
	//디버그 용 코드를 출시할때 영향을 주지 않도록 테스트용 빌드에서만 작동하게함


}
