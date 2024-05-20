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


	//�浹�� �̸��� ����,������ ����:this�� �־� �ڽ��� �浹�Ǵ°� ����
	FCollisionQueryParams collisionParams(SCENE_QUERY_STAT(Attack), false, UserChar);

	FHitResult outHitResult;
	TArray<FHitResult> outHitResults;
	TArray<FOverlapResult> outOverlapResults;
	const float attackRange = 0;
	const float capsuleRadius = 150.0f;
	bool isHit;

	//������ ���� ��ġ, ������ �������, ĸ��������Ʈ�� ������ũ��
	const FVector start = UserChar->GetActorLocation()+capsuleRadius*UserChar->GetActorForwardVector();

	FVector end= UserChar->GetActorLocation() - capsuleRadius * UserChar->GetActorForwardVector();


	//ĸ���� �߾���ġ
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

void ADRRPlayerActUnitProto3::Func2(AActor* User)
{
	ACharacterBase* UserChar = Cast<ACharacterBase>(User);

	UE_LOG(LogTemp, Log, TEXT("AttackHitCheck"));


	//�浹�� �̸��� ����,������ ����:this�� �־� �ڽ��� �浹�Ǵ°� ����
	FCollisionQueryParams collisionParams(SCENE_QUERY_STAT(Attack), false, UserChar);

	FHitResult outHitResult;
	TArray<FHitResult> outHitResults;
	TArray<FOverlapResult> outOverlapResults;
	const float attackRange = 0;
	const float capsuleRadius = 200.0f;
	bool isHit;

	//������ ���� ��ġ, ������ �������, ĸ��������Ʈ�� ������ũ��
	const FVector start = UserChar->GetActorLocation() + capsuleRadius * UserChar->GetActorForwardVector();

	FVector end = UserChar->GetActorLocation() - capsuleRadius * UserChar->GetActorForwardVector();


	//ĸ���� �߾���ġ
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

		//�浹����� ���� ������ ���ظ� ������ �Լ� ȣ��
		//�𸮾󿡼� ������ ��� ���͵��� �������� �Դ´ٴ� �����Ͽ� �����Լ�
		//����, �̺�Ʈ, ������Ʈ�ѷ�,������ ����
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


	//�浹�� �̸��� ����,������ ����:this�� �־� �ڽ��� �浹�Ǵ°� ����
	FCollisionQueryParams collisionParams(SCENE_QUERY_STAT(Attack), false, UserChar);

	FHitResult outHitResult;
	TArray<FHitResult> outHitResults;
	TArray<FOverlapResult> outOverlapResults;
	const float attackRange = 0;
	const float capsuleRadius = 250.0f;
	bool isHit;

	//������ ���� ��ġ, ������ �������, ĸ��������Ʈ�� ������ũ��
	const FVector start = UserChar->GetActorLocation() + capsuleRadius * UserChar->GetActorForwardVector();

	FVector end = UserChar->GetActorLocation() - capsuleRadius * UserChar->GetActorForwardVector();


	//ĸ���� �߾���ġ
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

		//�浹����� ���� ������ ���ظ� ������ �Լ� ȣ��
		//�𸮾󿡼� ������ ��� ���͵��� �������� �Դ´ٴ� �����Ͽ� �����Լ�
		//����, �̺�Ʈ, ������Ʈ�ѷ�,������ ����
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
