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


	//�浹�� �̸��� ����,������ ����:this�� �־� �ڽ��� �浹�Ǵ°� ����
	FCollisionQueryParams collisionParams(SCENE_QUERY_STAT(Attack), false, UserChar);

	FHitResult outHitResult;
	TArray<FHitResult> outHitResults;
	TArray<FOverlapResult> outOverlapResults;
	const float attackRange = 600.0f;
	const float attackRadius = 500.0f;
	bool isHit;


	//������ ���� ��ġ, ������ �������, ĸ��������Ʈ�� ������ũ��
	const FVector center = this->GetActorLocation()+User->GetActorForwardVector()*attackRange;
	const FVector start = center + attackRadius * FVector::ForwardVector;
	const FVector end = center + attackRadius * FVector::BackwardVector;



	//ĸ���� �߾���ġ
	FVector capsulePosition = start + (end - start) / 2.0f;


	isHit = GetWorld()->OverlapMultiByProfile(outOverlapResults, center, FQuat::Identity, TEXT("PlayerAttack"), FCollisionShape::MakeSphere(attackRadius), collisionParams);



	//DebugDraw
	bool isRemaining = false;
	FColor Color = isHit ? FColor::Green : FColor::Red;
	DrawDebugSphere(GetWorld(), center, attackRadius, 16, Color, isRemaining, 3.0f);




	if (isHit)
	{

		CDisplayLog::Log(TEXT("Collide"));
		for (auto& i : outOverlapResults)
		{
			if (i.GetActor())
			{

				ACharacterBase* Temp = Cast< ACharacterBase>(i.GetActor());
				if (Temp != nullptr)
				{

					float defaultDamage = 6.0f;
					float damageResult = defaultDamage*GetActData()->SkillCoefficient * UserChar->physicsAttack;



					CDisplayLog::Log(TEXT("Pillar"));

					ADRRPlayerStonePillarProto* Pillar = GetWorld()->SpawnActor<ADRRPlayerStonePillarProto>(StonePillar, Temp->GetActorLocation(), Temp->GetActorRotation());
					Pillar->Init(User, damageResult);

				}

			}
		}
	}



	//��ο� ����� ������ �����϶���
	//����� �� �ڵ带 ����Ҷ� ������ ���� �ʵ��� �׽�Ʈ�� ���忡���� �۵��ϰ���


}
