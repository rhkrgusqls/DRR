// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRPassiveActComponent.h"
#include "CharacterBase/Effect/DRROnAttackEffect.h"
#include "CharacterBase/Effect/DRROnAutoEffect.h"
#include "CharacterBase/Effect/DRROnDamageEffect.h"
#include "CharacterBase/Effect/DRROnHitEffect.h"
#include "Effect/DRREffectUnitBase.h"
#include "DataAsset/DA_EffectData.h"
#include "Utilities/UtilityList.h"
// Sets default values for this component's properties
UDRRPassiveActComponent::UDRRPassiveActComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDRRPassiveActComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDRRPassiveActComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AutoUpdate(DeltaTime);
	AutoUse();

}

void UDRRPassiveActComponent::AutoUpdate(float DeltaTime)
{
	for (int i = 0; i < AutoEffects.Num(); i++)
	{
		AutoEffects[i]->Tick(DeltaTime);
		if (AutoEffects[i]->CheckExpire())
		{
			AutoEffects[i]->EndEffect(GetOwner());
			AutoEffects.RemoveAt(i);
		}
	}
	for (int i = 0; i < HittedEffects.Num(); i++)
	{
		HittedEffects[i]->Tick(DeltaTime);
		if (HittedEffects[i]->CheckExpire())
		{
			HittedEffects[i]->EndEffect(GetOwner());
			HittedEffects.RemoveAt(i);
		}
	}
	for (int i = 0; i < DamagedEffects.Num(); i++)
	{
		DamagedEffects[i]->Tick(DeltaTime);
		if (DamagedEffects[i]->CheckExpire())
		{
			DamagedEffects[i]->EndEffect(GetOwner());
			DamagedEffects.RemoveAt(i);
		}
	}
	for (int i = 0; i < AttackEffects.Num(); i++)
	{
		AttackEffects[i]->Tick(DeltaTime);
		if (AttackEffects[i]->CheckExpire())
		{
			AttackEffects[i]->EndEffect(GetOwner());
			AttackEffects.RemoveAt(i);
		}
	}
}

void UDRRPassiveActComponent::AutoUse()
{
	for (int i = 0; i < AutoEffects.Num(); i++)
	{
		if (AutoEffects[i]->CheckReadyToUse())
		{
			CLog::Log("Use");
			CLog::Log(i);
			AutoEffects[i]->UseEffect(GetOwner());
			AutoEffects[i]->DelayReset();
		}

		
	}
}

void UDRRPassiveActComponent::AttackUse()
{
	for (auto i : AttackEffects)
	{
		if (i->CheckReadyToUse())
		{
			i->UseEffect(GetOwner());
			i->DelayReset();
		}
	}
}

void UDRRPassiveActComponent::DamagedUse(TArray<AActor*> Victims)
{
	for (auto i : DamagedEffects)
	{
		if (i->CheckExpire())
		{
			if (i->CheckReadyToUse())
			{
				for (auto j : Victims)
				{
					i->UseEffect(j);

				}
				i->DelayReset();

			}
		}

	}
}

void UDRRPassiveActComponent::HittedUse(AActor* Attacker)
{
	for (auto i : HittedEffects)
	{
		if (i->CheckReadyToUse())
		{
			i->UseEffect(Attacker);
			i->DelayReset();
		}
	}
}

void UDRRPassiveActComponent::AddEffect(TSubclassOf<class ADRREffectUnitBase> Effect, AActor* User)
{

		
	if (CheckDuplicate(Effect,User))
	{
		return;
	}
	//ADRREffectUnitBase* Default = Cast<ADRREffectUnitBase>(Effect->GetDefaultObject());
	//ADRREffectUnitBase* Temp = NewObject<ADRREffectUnitBase>();
	ADRREffectUnitBase* Temp = GetWorld()->SpawnActor <ADRREffectUnitBase>(Effect);
	//Temp->SetData(Default->GetEffectData());
	Temp->SetUser(User);
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, false);
	Temp->AttachToActor(User, AttachmentRules);
	Temp->SetTarget(GetOwner());
	switch (Temp->GetEffectData()->UseType)
	{
	case EPassiveType::Hit :
		CreateHit(Temp);
		CLog::Log("CreateHit");
		break;
	case EPassiveType::Attack:
		CreateAttack(Temp);
		CLog::Log("CreateAttack");
		break;
	case EPassiveType::Auto:
		CreateAuto(Temp);
		CLog::Log("CreateAuto");
		break;
	case EPassiveType::Damage:
		CreateDamage(Temp);
		CLog::Log("CreateDamage");

		break;
	default:
		break;
	}

	

}

bool UDRRPassiveActComponent::RemoveEffect(TSubclassOf<class ADRREffectUnitBase> Effect)
{
	
	return false;
}

bool UDRRPassiveActComponent::RemoveEffect(TSubclassOf<class ADRREffectUnitBase> Effect, AActor* User)
{
	return false;
}

bool UDRRPassiveActComponent::CheckDuplicate(TSubclassOf<class ADRREffectUnitBase> Effect, AActor* User)
{
	ADRREffectUnitBase* Temp = Cast<ADRREffectUnitBase>(Effect->GetDefaultObject());
	switch (Temp->GetEffectData()->UseType)
	{
	case EPassiveType::Hit:
		for (auto i : HittedEffects)
		{
			if (i->GetEffectData()->PassiveName.Equals(Temp->GetEffectData()->PassiveName)&&i->GetUser()== User)
			{
				i->ExpireReset(Temp);
			
				return true;
			}

		}

		break;
	case EPassiveType::Attack:
		for (auto i : AttackEffects)
		{
			if (i->GetEffectData()->PassiveName.Equals(Temp->GetEffectData()->PassiveName) && i->GetUser() == User)
			{
				i->ExpireReset(Temp);
				return true;
			}

		}
		break;
	case EPassiveType::Auto:
		for (auto i : AutoEffects)
		{
			if (i->GetEffectData()->PassiveName.Equals(Temp->GetEffectData()->PassiveName) && i->GetUser() == User)
			{
				i->ExpireReset(Temp);
				return true;
			}

		}
		break;
	case EPassiveType::Damage:
		for (auto i : DamagedEffects)
		{
			if (i->GetEffectData()->PassiveName.Equals(Temp->GetEffectData()->PassiveName) && i->GetUser() == User)
			{
				i->ExpireReset(Temp);
				return true;
			}

		}


		break;
	default:
		break;
	}

	return false;
}

void UDRRPassiveActComponent::CreateAuto(class ADRREffectUnitBase* Effect)
{

	DRROnAutoEffect* OnAutoTemp = new DRROnAutoEffect(Effect);
	AutoEffects.Add(OnAutoTemp);
	OnAutoTemp->BeginEffect(GetOwner());
}

void UDRRPassiveActComponent::CreateHit(class ADRREffectUnitBase* Effect)
{
	DRROnHitEffect* OnHitTemp = new DRROnHitEffect(Effect);
	HittedEffects.Add(OnHitTemp);
	OnHitTemp->BeginEffect(GetOwner());
}

void UDRRPassiveActComponent::CreateDamage(class ADRREffectUnitBase* Effect)
{
	DRROnDamageEffect* OnDamageTemp = new DRROnDamageEffect(Effect);
	DamagedEffects.Add(OnDamageTemp);
	OnDamageTemp->BeginEffect(GetOwner());

}

void UDRRPassiveActComponent::CreateAttack(class ADRREffectUnitBase* Effect)
{
	DRROnAttackEffect* OnAttackTemp = new DRROnAttackEffect(Effect);
	AttackEffects.Add(OnAttackTemp);
	OnAttackTemp->BeginEffect(GetOwner());
}

