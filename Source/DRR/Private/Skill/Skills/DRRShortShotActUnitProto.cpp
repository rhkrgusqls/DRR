// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills/DRRShortShotActUnitProto.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Engine/DamageEvents.h"


#include "Utilities/CLog.h"


UDRRShortShotActUnitProto::UDRRShortShotActUnitProto()
{
	ConstructorHelpers::FObjectFinder<UDA_ActData> DataAssetRef(TEXT("/Script/DRR.DA_ShortShotActData'/Game/Blueprints/Weapon/Weapon1/DA_ShortShotWeaponAct1.DA_ShortShotWeaponAct1'"));
	if (DataAssetRef.Object)
	{
		ActData = DataAssetRef.Object;
	}
	CLog::Log("ActDataCheck");
	CLog::Log(ActData != nullptr);
	CLog::Log(ActData->ActionName);
	
}

TArray<FOnActFuncDelegate> UDRRShortShotActUnitProto::GetActFunc()
{
	TArray<FOnActFuncDelegate> arr;

	FOnActFuncDelegate temp;
	temp.BindUObject(this, &UDRRShortShotActUnitProto::Func1);
	arr.Add(temp);
	return arr;
}

void UDRRShortShotActUnitProto::BeginFunc(AActor* Owner)
{
	CLog::Log("ActBeginFunc");
}

void UDRRShortShotActUnitProto::EndFunc(AActor* Owner)
{
	CLog::Log("ActEndFunc");
}

void UDRRShortShotActUnitProto::Func1(AActor* Owner)
{
	CLog::Log("DamageTestActFunc1");

	ACharacter* User = Cast<ACharacter>(Owner);

	UE_LOG(LogTemp, Log, TEXT("AttackHitCheck"));


	//충돌에 이름을 붙임,무시할 액터:this를 넣어 자신이 충돌되는걸 방지
	FCollisionQueryParams collisionParams(SCENE_QUERY_STAT(Attack), false, User);

	FHitResult outHitResult;
	TArray<FHitResult> outHitResults;
	TArray<FOverlapResult> outOverlapResults;
	const float attackRange = 150.0f;
	const float capsuleRadius = 50.0f;
	bool isHit;

	//액터의 현재 위치, 액터의 정면백터, 캡슐컴포넌트의 반지름크기
	const FVector start = User->GetActorLocation() + User->GetActorForwardVector() * User->GetCapsuleComponent()->GetScaledCapsuleRadius();
	
	FVector end;


	//캡슐의 중앙위치
	FVector capsulePosition = start + (end - start) / 2.0f;

	float halfHeight = attackRange / 2.0f;

	end = start + User->GetActorForwardVector() * attackRange;
	isHit = GetWorld()->SweepSingleByChannel(outHitResult, start, end, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(capsuleRadius * 2), collisionParams);

	//DebugDraw
	bool isRemaining = false;
	FColor Color = isHit ? FColor::Green : FColor::Red;
	DrawDebugCapsule(GetWorld(), end, halfHeight, capsuleRadius * 2, FRotationMatrix::MakeFromZ(User->GetActorForwardVector()).ToQuat(), Color, isRemaining, 3.0f);

	

	
	if (isHit)
	{

		FDamageEvent damageEvent;
		CLog::Log("Hitted");
		//충돌대상의 액터 가져와 피해를 입히는 함수 호출
		//언리얼에서 만들어둔 모든 액터들은 데미지를 입는다는 가정하에 만든함수
		//피해, 이벤트, 나의컨트롤러,가해자 액터

		if (outHitResult.GetActor())
		{

			outHitResult.GetActor()->TakeDamage(40.0f, damageEvent, User->GetController(), User);
		}
	}

	//드로우 디버그 가능한 상태일때만
	//디버그 용 코드를 출시할때 영향을 주지 않도록 테스트용 빌드에서만 작동하게함


}
