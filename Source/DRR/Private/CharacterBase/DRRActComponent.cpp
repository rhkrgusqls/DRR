// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRActComponent.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "DataAsset/DA_ActData.h"
#include "DataAsset/DA_ChargeActData.h"
#include "DataAsset/DA_CastActData.h"
#include "DataAsset/DA_ComboActData.h"
#include "DataAsset/DA_ShortShotActData.h"
#include "Interface/DRRActableInterface.h"
#include "CharacterBase/DRRAct.h"
#include "CharacterBase/DRRShortShotAct.h"
#include "CharacterBase/DRRCastAct.h"
#include "CharacterBase/DRRChargeAct.h"
#include "CharacterBase/DRRComboAct.h"
#include "CharacterBase/DRRTriggerAct.h"
#include "Skill/DRRActUnitBase.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/CapsuleComponent.h"

#include "Utilities/UtilityList.h"

// Sets default values for this component's properties
UDRRActComponent::UDRRActComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Actor = nullptr;
	TryInput = false;

	//Take Item Section
	ActActions.Add(FOnActDelegateWrapper(FOnActDelegate::CreateUObject(this, &UDRRActComponent::ShortShot)));
	ActActions.Add(FOnActDelegateWrapper(FOnActDelegate::CreateUObject(this, &UDRRActComponent::Charging)));
	ActActions.Add(FOnActDelegateWrapper(FOnActDelegate::CreateUObject(this, &UDRRActComponent::Casting)));
	ActActions.Add(FOnActDelegateWrapper(FOnActDelegate::CreateUObject(this, &UDRRActComponent::Combo)));
	ActActions.Add(FOnActDelegateWrapper(FOnActDelegate::CreateUObject(this, &UDRRActComponent::Trigger)));



	// ...
}


// Called when the game starts
void UDRRActComponent::BeginPlay()
{
	Super::BeginPlay();

	
}



void UDRRActComponent::AfterAct()
{
	hasNextAct= Actor->AfterAct();
	
}


// Called every frame
void UDRRActComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDRRActComponent::Act(IDRRActableInterface* Actable)
{


	CLog::Log("Act");
	CLog::Log((uint8)Actable->GetActData()->Type);
	

	//실행중인 행동이 없거나 이번에 들어온 행동입력이 다른행동일경우
	if (Actor == nullptr)
	{
		
		CLog::Log("NewAct");
		SetActor(Actable);
		Actor->SetActor(Actable);
		BeginAct();
		return;
	}
	//같은 명령이라면 같은 행동선에서 다른 행동. 아니라면 새로운 행동, 트리거타입의 행동이 진행중일떄.
	if (Actor->GetCurAct()->ActionName.Equals(Actable->GetActData()->ActionName))
	{
		CLog::Log("AfterAct");
		AfterAct();

		return;
	}

}

void UDRRActComponent::ActRelease(IDRRActableInterface* Actable)
{
	if (Actor == nullptr||Actor->GetCurAct()->ActionName!=Actable->GetActData()->ActionName)
	{
		return;
	}
	CLog::Log("KeyRelease");
	Actor->ActRelease();
	if (Actor->GetCurAct()->Type==EActType::Charging)
	{
		AfterAct();
		EndTimer();
		CheckAct();
	}
}

void UDRRActComponent::ActFunc()
{
	CLog::Log("ActFunc");

	if (Actor == nullptr)
	{
		return;
	}

	Actor->DoAct().ExecuteIfBound(GetOwner());

}
DRRAct* UDRRActComponent::ShortShot( IDRRActableInterface* Target)
{
	CLog::Log("MakeShortShot");
	Actor = new DRRShortShotAct();

	return Actor;

}

DRRAct* UDRRActComponent::Charging(IDRRActableInterface* Target)
{
	CLog::Log("MakeCharging");
	Actor = new DRRChargeAct();;;
	return Actor;
}	

DRRAct* UDRRActComponent::Casting(IDRRActableInterface* Target)
{
	CLog::Log("MakeCasting");
	Actor = new DRRCastAct();;
	return Actor;
}

DRRAct* UDRRActComponent::Combo(IDRRActableInterface* Target)
{
	CLog::Log("MakeCombo");
	Actor = new DRRComboAct();;

	return Actor;
}

DRRAct* UDRRActComponent::Trigger(IDRRActableInterface* Target)
{
	CLog::Log("MakeCombo");
	Actor = new DRRTriggerAct();;

	return Actor;
}

void UDRRActComponent::BeginAct()
{

	CLog::Log("UDRRActComponent::BeginAct");

	UAnimInstance* animInstance = Cast<ACharacter>(GetOwner())->GetMesh()->GetAnimInstance();
	//몽타주 실행
	animInstance->Montage_Play(Actor->GetCurAct()->ActionMontage);


	Actor->DoBeginAct().ExecuteIfBound(GetOwner());
	//몽타주가 끝날떄 호출되는델리게이트
	FOnMontageEnded endDelegate;
	//델리게이트 바인딩
	endDelegate.BindUObject(this, &UDRRActComponent::EndAct);
	//애님인스턴스가 엔드델리게이트로 사용할 델리게이트 설정
	animInstance->Montage_SetEndDelegate(endDelegate, Actor->GetCurAct()->ActionMontage);
	hasNextAct = Actor->BeginAct();
	//콤보체크타이머 세팅
	CheckActTimer();
}

void UDRRActComponent::CheckActTimer()
{
	float NextCheckTime = Actor->GetNextTime();
	if (NextCheckTime > 0.0f)
	{


		//타이머 설정: (타임핸들러, 객체, 실행할 함수,지연시간, 루프 여부)
		GetWorld()->GetTimerManager().SetTimer(ActTimerHandle, this, &UDRRActComponent::CheckAct, NextCheckTime, false);
	}
}

void UDRRActComponent::EndTimer()
{
	
	if (ActTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ActTimerHandle);
	}
}

void UDRRActComponent::CheckAct()
{
	//콤보타이머 핸들 비활성화
	EndTimer();
	
	CLog::Log("UDRRActComponent::CheckAct");


	if (hasNextAct)
	{
		CLog::Log("ActNextMotion");
		
		uint8 curActCount=Actor->NextAct();

		UAnimInstance* animInstance = Cast<ACharacter>(GetOwner())->GetMesh()->GetAnimInstance();
		//실행할 색션이름 지정 포맷 FString 앞에는 *을 꼭붙여줘야함

		CLog::Log("UDRRActComponent::GetMontgeSectionName");
		FName nextSectionName(Actor->GetMontgeSectionName());
		CLog::Log(nextSectionName.ToString());
			//몽타주 실행
		//몽타주의 특정 이름의 액션 실행 
		animInstance->Montage_JumpToSection(nextSectionName, Actor->GetCurAct()->ActionMontage);
		
		//콤보타이머 활성화
		CheckActTimer();
		hasNextAct = Actor->NextReset();

	}
	else
	{
		CLog::Log("Finish Montage");
		CLog::Log(Actor->GetCurAct()->ActionName);
		
		PrevActor = Actor;
		Actor = nullptr;
		// 이유를 알수 없이 애님몽타주가 끝났는데 Check를 한번 더하고있다. 이유를 찾아봐야할듯
		if (PrevActor == nullptr)
		{
			return;
		}
		bool another = PrevActor->GetCurAct()->HasAnotherAct;
		auto nextAct = PrevActor->GetCurAct()->NextActUnit.GetDefaultObject();
		bool check = PrevActor->GetConditionCheckFunc().Execute(GetOwner());
		if(PrevActor!=nullptr&& another && check &&nextAct!=nullptr)
		{
			CLog::Log("TryTriggerAct");
			Act(nextAct);
		}

	}

}

void UDRRActComponent::EndAct(UAnimMontage* targetMontage, bool isInteruped)
{
	CLog::Log("UDRRActComponent::EndAct");
	CLog::Log(targetMontage->GetName());

	
	if (PrevActor!=nullptr&&PrevActor->DoEndAct().IsBound())
	{
		PrevActor->DoEndAct().Execute(GetOwner());

	}
	EraseAct();


}

void UDRRActComponent::ClearMontageAct()
{
	EndTimer();
	
}

void UDRRActComponent::BeginDestroy()
{
	Super::BeginDestroy();
	if (Actor != nullptr)
	{
		Actor->EndAct();
		delete(Actor);
	}
	if (PrevActor != nullptr)
	{
		PrevActor->EndAct();
		delete(PrevActor);
	}
}

void UDRRActComponent::EraseAct()
{
	CLog::Log("UDRRActComponent::EraseAct");
	if (PrevActor != nullptr)
	{
		PrevActor->EndAct();
		delete(PrevActor);
		PrevActor = nullptr;
	}
}

void UDRRActComponent::SetActor(IDRRActableInterface* Target)
{
	//델리게이트랩퍼로 스위치 대신 사용하려면 UFUNCTION을 써야하는데 오류 해결이 난해함 나중에 강사님께 여쭤보자
	//ActActions[(uint8)Target->GetActData()->Type];

	
	switch (Target->GetActData()->Type)
	{
	case EActType::ShortShot:
		CLog::Log("ShortShot");
		Actor = new DRRShortShotAct();;
		break;
	case EActType::Charging:
		CLog::Log("Charging");
		Actor = new DRRChargeAct();;
		break;
	case EActType::Casting:
		CLog::Log("Casting");
		Actor = new DRRCastAct();;
		break;
	case EActType::Combo:
		CLog::Log("Combo");
		Actor = new DRRComboAct();
		break;
	case EActType::Trigger:
		CLog::Log("Trigger");
		Actor = new DRRTriggerAct();
		break;
	}
}



