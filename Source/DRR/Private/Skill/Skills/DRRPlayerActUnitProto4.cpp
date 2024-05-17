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
	const float capsuleRadius = 200.0f;
	bool isHit;

	//������ ���� ��ġ, ������ �������, ĸ��������Ʈ�� ������ũ��
	const FVector start = UserChar->GetActorLocation() + UserChar->GetActorForwardVector() * UserChar->GetCapsuleComponent()->GetScaledCapsuleRadius();

	FVector end;


	//ĸ���� �߾���ġ
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

		//�浹����� ���� ������ ���ظ� ������ �Լ� ȣ��
		//�𸮾󿡼� ������ ��� ���͵��� �������� �Դ´ٴ� �����Ͽ� �����Լ�
		//����, �̺�Ʈ, ������Ʈ�ѷ�,������ ����

		for (auto& i : outHitResults)
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

	//��ο� ����� ������ �����϶���
	//����� �� �ڵ带 ����Ҷ� ������ ���� �ʵ��� �׽�Ʈ�� ���忡���� �۵��ϰ���


}
