// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRPlayerActUnitProto.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Engine/DamageEvents.h"
#include "CharacterBase/CharacterBase.h"

#include "Utilities/CLog.h"
ADRRPlayerActUnitProto::ADRRPlayerActUnitProto()
{
	ConstructorHelpers::FObjectFinder<UDA_ActData> DataAssetRef(TEXT("/Script/DRR.DA_ShortShotActData'/Game/Blueprints/Weapon/PlayerTestWeapon/DA_PlayerWeaponProtoAct1.DA_PlayerWeaponProtoAct1'"));
	if (DataAssetRef.Object)
	{
		ActData = DataAssetRef.Object;
	}
	CLog::Log("ActDataCheck");
	CLog::Log(ActData != nullptr);
	CLog::Log(ActData->ActionName);
	
}

TArray<FOnActFuncDelegate> ADRRPlayerActUnitProto::GetActFunc()
{
	TArray<FOnActFuncDelegate> arr;

	FOnActFuncDelegate temp;
	temp.BindUObject(this, &ADRRPlayerActUnitProto::Func1);
	arr.Add(temp);
	return arr;
}

void ADRRPlayerActUnitProto::BeginFunc(AActor* User)
{
	CLog::Log("ActBeginFunc");
}

void ADRRPlayerActUnitProto::EndFunc(AActor* User)
{
	CLog::Log("ActEndFunc");
}

void ADRRPlayerActUnitProto::Func1(AActor* User)
{
	CLog::Log("DamageTestActFunc1");

	ACharacterBase* UserChar = Cast<ACharacterBase>(User);

	UE_LOG(LogTemp, Log, TEXT("AttackHitCheck"));


	//�浹�� �̸��� ����,������ ����:this�� �־� �ڽ��� �浹�Ǵ°� ����
	FCollisionQueryParams collisionParams(SCENE_QUERY_STAT(Attack), false, UserChar);

	FHitResult outHitResult;
	TArray<FHitResult> outHitResults;
	TArray<FOverlapResult> outOverlapResults;
	const float attackRange = 150.0f;
	const float capsuleRadius = 50.0f;
	bool isHit;

	//������ ���� ��ġ, ������ �������, ĸ��������Ʈ�� ������ũ��
	const FVector start = UserChar->GetActorLocation() + UserChar->GetActorForwardVector() * UserChar->GetCapsuleComponent()->GetScaledCapsuleRadius();

	FVector end;


	//ĸ���� �߾���ġ
	FVector capsulePosition = start + (end - start) / 2.0f;

	float halfHeight = attackRange / 2.0f;

	end = start + UserChar->GetActorForwardVector() * attackRange;
	isHit = GetWorld()->SweepSingleByChannel(outHitResult, start, end, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3, FCollisionShape::MakeSphere(capsuleRadius * 2), collisionParams);
	


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

	//��ο� ����� ������ �����϶���
	//����� �� �ڵ带 ����Ҷ� ������ ���� �ʵ��� �׽�Ʈ�� ���忡���� �۵��ϰ���


}
