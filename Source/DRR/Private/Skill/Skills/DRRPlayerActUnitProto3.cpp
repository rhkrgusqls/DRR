// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRPlayerActUnitProto3.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Engine/DamageEvents.h"
#include "CharacterBase/CharacterBase.h"
#include "PhysicsEngine/PhysicsSettings.h"
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
	const float attackRange = 50;
	const float attackRadius = 150.0f;
	bool isHit;

	//������ ���� ��ġ, ������ �������, ĸ��������Ʈ�� ������ũ��
	const FVector center = UserChar->GetActorLocation()+UserChar->GetActorForwardVector()* attackRange;
	const FVector start = center+FVector::ForwardVector* attackRadius;
	const FVector end = center+FVector::BackwardVector* attackRadius;





	isHit = GetWorld()->OverlapMultiByProfile(outOverlapResults, center,FQuat::Identity, TEXT("PlayerAttack"), FCollisionShape::MakeSphere(attackRadius), collisionParams);



	//DebugDraw
	bool isRemaining = false;
	FColor Color = isHit ? FColor::Green : FColor::Red;
	DrawDebugSphere(GetWorld(), center, attackRadius, 16, Color, isRemaining, 3.0f);




	if (isHit)
	{

		FDamageEvent damageEvent;

		//�浹����� ���� ������ ���ظ� ������ �Լ� ȣ��
		//�𸮾󿡼� ������ ��� ���͵��� �������� �Դ´ٴ� �����Ͽ� �����Լ�
		//����, �̺�Ʈ, ������Ʈ�ѷ�,������ ����
		ACharacterBase* Temp;

		for (auto& i : outOverlapResults)
		{
			if (i.GetActor()!=nullptr)
			{
				Temp = Cast< ACharacterBase>(i.GetActor());
				if (Temp != nullptr)
				{

					




					const float defaultDamage = 4.0f;
					float damageResult = GetActData()->SkillCoefficient * defaultDamage * UserChar->physicsAttack;

					Temp->ReciveAttack(damageResult);


				}
			}
		}

	}

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
	const float attackRange = 50;
	const float attackRadius = 200.0f;
	bool isHit;

	//������ ���� ��ġ, ������ �������, ĸ��������Ʈ�� ������ũ��
	const FVector center = UserChar->GetActorLocation() + UserChar->GetActorForwardVector() * attackRange;
	const FVector start = center + FVector::ForwardVector * attackRadius;
	const FVector end = center + FVector::BackwardVector * attackRadius;





	isHit = GetWorld()->OverlapMultiByProfile(outOverlapResults, center, FQuat::Identity, TEXT("PlayerAttack"), FCollisionShape::MakeSphere(attackRadius), collisionParams);



	//DebugDraw
	bool isRemaining = false;
	FColor Color = isHit ? FColor::Green : FColor::Red;
	DrawDebugSphere(GetWorld(), center, attackRadius, 16, Color, isRemaining, 3.0f);




	if (isHit)
	{

		FDamageEvent damageEvent;

		//�浹����� ���� ������ ���ظ� ������ �Լ� ȣ��
		//�𸮾󿡼� ������ ��� ���͵��� �������� �Դ´ٴ� �����Ͽ� �����Լ�
		//����, �̺�Ʈ, ������Ʈ�ѷ�,������ ����
		ACharacterBase* Temp;

		for (auto& i : outOverlapResults)
		{
			if (i.GetActor() != nullptr)
			{
				Temp = Cast< ACharacterBase>(i.GetActor());
				if (Temp != nullptr)
				{
					

					const float defaultDamage = 6.0f;
					float damageResult = GetActData()->SkillCoefficient * defaultDamage * UserChar->physicsAttack;

					Temp->ReciveAttack(damageResult);


				}
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
	const float attackRange = 50;
	const float attackRadius = 250.0f;
	bool isHit;

	//������ ���� ��ġ, ������ �������, ĸ��������Ʈ�� ������ũ��
	const FVector center = UserChar->GetActorLocation() + UserChar->GetActorForwardVector() * attackRange;
	const FVector start = center + FVector::ForwardVector * attackRadius;
	const FVector end = center + FVector::BackwardVector * attackRadius;





	isHit = GetWorld()->OverlapMultiByProfile(outOverlapResults, center, FQuat::Identity, TEXT("PlayerAttack"), FCollisionShape::MakeSphere(attackRadius), collisionParams);



	//DebugDraw
	bool isRemaining = false;
	FColor Color = isHit ? FColor::Green : FColor::Red;
	DrawDebugSphere(GetWorld(), center, attackRadius, 16, Color, isRemaining, 3.0f);




	if (isHit)
	{

		FDamageEvent damageEvent;

		//�浹����� ���� ������ ���ظ� ������ �Լ� ȣ��
		//�𸮾󿡼� ������ ��� ���͵��� �������� �Դ´ٴ� �����Ͽ� �����Լ�
		//����, �̺�Ʈ, ������Ʈ�ѷ�,������ ����
		ACharacterBase* Temp;

		for (auto& i : outOverlapResults)
		{
			if (i.GetActor() != nullptr)
			{
				Temp = Cast< ACharacterBase>(i.GetActor());
				if (Temp != nullptr)
				{
					UPrimitiveComponent* OverlappedComponent = Cast<UPrimitiveComponent>(i.GetComponent());
					if (OverlappedComponent && OverlappedComponent->IsSimulatingPhysics())
					{
						FVector PushDirection = Temp->GetActorLocation() - center;
						PushDirection.Normalize();
						float PushStrength = 1000.0f;

						FVector Impulse = PushDirection * PushStrength;

						OverlappedComponent->AddImpulse(Impulse);
					}

					const float defaultDamage = 8.0f;
					float damageResult = GetActData()->SkillCoefficient * defaultDamage * UserChar->physicsAttack;

					Temp->ReciveAttack(damageResult);


				}
			}
		}

	}

}
