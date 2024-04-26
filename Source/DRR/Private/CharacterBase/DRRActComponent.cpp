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
#include "CharacterBase/BattleAct/DRRAct.h"
#include "CharacterBase/BattleAct/DRRShortShotAct.h"
#include "CharacterBase/BattleAct/DRRCastAct.h"
#include "CharacterBase/BattleAct/DRRChargeAct.h"
#include "CharacterBase/BattleAct/DRRComboAct.h"
#include "CharacterBase/BattleAct/DRRTriggerAct.h"
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
	

	//�������� �ൿ�� ���ų� �̹��� ���� �ൿ�Է��� �ٸ��ൿ�ϰ��
	if (Actor == nullptr)
	{
		
		CLog::Log("NewAct");
		SetActor(Actable);
		Actor->SetActor(Actable);
		BeginAct();
		return;
	}
	//���� ����̶�� ���� �ൿ������ �ٸ� �ൿ. �ƴ϶�� ���ο� �ൿ, Ʈ����Ÿ���� �ൿ�� �������ϋ�.
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
	//��Ÿ�� ����
	animInstance->Montage_Play(Actor->GetCurAct()->ActionMontage);


	Actor->DoBeginAct().ExecuteIfBound(GetOwner());
	//��Ÿ�ְ� ������ ȣ��Ǵµ�������Ʈ
	FOnMontageEnded endDelegate;
	//��������Ʈ ���ε�
	endDelegate.BindUObject(this, &UDRRActComponent::EndAct);
	//�ִ��ν��Ͻ��� ���嵨������Ʈ�� ����� ��������Ʈ ����
	animInstance->Montage_SetEndDelegate(endDelegate, Actor->GetCurAct()->ActionMontage);
	hasNextAct = Actor->BeginAct();
	//�޺�üũŸ�̸� ����
	CheckActTimer();
}

void UDRRActComponent::CheckActTimer()
{
	float NextCheckTime = Actor->GetNextTime();
	if (NextCheckTime > 0.0f)
	{


		//Ÿ�̸� ����: (Ÿ���ڵ鷯, ��ü, ������ �Լ�,�����ð�, ���� ����)
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
	//�޺�Ÿ�̸� �ڵ� ��Ȱ��ȭ
	EndTimer();
	
	CLog::Log("UDRRActComponent::CheckAct");


	if (hasNextAct)
	{
		CLog::Log("ActNextMotion");
		
		uint8 curActCount=Actor->NextAct();

		UAnimInstance* animInstance = Cast<ACharacter>(GetOwner())->GetMesh()->GetAnimInstance();
		//������ �����̸� ���� ���� FString �տ��� *�� ���ٿ������

		CLog::Log("UDRRActComponent::GetMontgeSectionName");
		FName nextSectionName(Actor->GetMontgeSectionName());
		CLog::Log(nextSectionName.ToString());
			//��Ÿ�� ����
		//��Ÿ���� Ư�� �̸��� �׼� ���� 
		animInstance->Montage_JumpToSection(nextSectionName, Actor->GetCurAct()->ActionMontage);
		
		//�޺�Ÿ�̸� Ȱ��ȭ
		CheckActTimer();
		hasNextAct = Actor->NextReset();

	}
	else
	{
		CLog::Log("Finish Montage");
		CLog::Log(Actor->GetCurAct()->ActionName);
		
		PrevActor = Actor;
		Actor = nullptr;
		// ������ �˼� ���� �ִԸ�Ÿ�ְ� �����µ� Check�� �ѹ� ���ϰ��ִ�. ������ ã�ƺ����ҵ�
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
	//��������Ʈ���۷� ����ġ ��� ����Ϸ��� UFUNCTION�� ����ϴµ� ���� �ذ��� ������ ���߿� ����Բ� ���庸��
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



