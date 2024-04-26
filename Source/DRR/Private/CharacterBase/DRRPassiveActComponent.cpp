// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRPassiveActComponent.h"
#include "CharacterBase/Effect/DRROnAttackEffect.h"
#include "CharacterBase/Effect/DRROnAutoEffect.h"
#include "CharacterBase/Effect/DRROnDamageEffect.h"
#include "CharacterBase/Effect/DRROnHitEffect.h"
#include "Effect/DRREffectUnitBase.h"
#include "DataAsset/DA_EffectData.h"

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

}

void UDRRPassiveActComponent::AutoUpdate(float DeltaTime)
{
	for (auto i : AutoEffects)
	{
		i->Tick(DeltaTime);
		if (i->CheckExpire())
		{
			i->EndEffect(GetOwner());
			AutoEffects.Remove(i);
		}

	}
	for (auto i : HittedEffects)
	{
		i->Tick(DeltaTime);
		if (i->CheckExpire())
		{
			i->EndEffect(GetOwner());
			HittedEffects.Remove(i);
		}
	}
	for (auto i : DamagedEffects)
	{
		i->Tick(DeltaTime);
		if (i->CheckExpire())
		{
			i->EndEffect(GetOwner());
			DamagedEffects.Remove(i);
		}
	}
	for (auto i : AttackEffects)
	{
		i->Tick(DeltaTime);
		if (i->CheckExpire())
		{
			i->EndEffect(GetOwner());
			AttackEffects.Remove(i);
		}
	}
}

void UDRRPassiveActComponent::AutoUse()
{
	for (auto i : AutoEffects)
	{
		
		if (i->CheckReadyToUse())
		{
			i->UseEffect(GetOwner());
			i->DelayReset();
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

void UDRRPassiveActComponent::AddEffect(ADRREffectUnitBase* Effect)
{

		
	if (CheckDuplicate(Effect))
	{
		Effect->RemoveEffect();
		return;
	}
	Effect->SetTarget(GetOwner());
	switch (Effect->GetEffectData()->UseType)
	{
	case EPassiveType::Hit :
		CreateHit(Effect);

		break;
	case EPassiveType::Attack:
		CreateAttack(Effect);
		break;
	case EPassiveType::Auto:
		CreateAuto(Effect);
		break;
	case EPassiveType::Damage:
		CreateDamage(Effect);

		break;
	default:
		break;
	}

	

}

bool UDRRPassiveActComponent::RemoveEffect(ADRREffectUnitBase* Effect)
{
	return false;
}

bool UDRRPassiveActComponent::CheckDuplicate(ADRREffectUnitBase* Effect)
{
	switch (Effect->GetEffectData()->UseType)
	{
	case EPassiveType::Hit:
		for (auto i : HittedEffects)
		{
			if (i->GetEffectData()->PassiveName.Equals(Effect->GetEffectData()->PassiveName)&&i->GetUser()==Effect->GetUser())
			{
				i->ExpireReset(Effect);
			
				return true;
			}

		}

		break;
	case EPassiveType::Attack:
		for (auto i : AttackEffects)
		{
			if (i->GetEffectData()->PassiveName.Equals(Effect->GetEffectData()->PassiveName) && i->GetUser() == Effect->GetUser())
			{
				i->ExpireReset(Effect);
				return true;
			}

		}
		break;
	case EPassiveType::Auto:
		for (auto i : AutoEffects)
		{
			if (i->GetEffectData()->PassiveName.Equals(Effect->GetEffectData()->PassiveName) && i->GetUser() == Effect->GetUser())
			{
				i->ExpireReset(Effect);
				return true;
			}

		}
		break;
	case EPassiveType::Damage:
		for (auto i : DamagedEffects)
		{
			if (i->GetEffectData()->PassiveName.Equals(Effect->GetEffectData()->PassiveName) && i->GetUser() == Effect->GetUser())
			{
				i->ExpireReset(Effect);
				return true;
			}

		}


		break;
	default:
		break;
	}

	return false;
}

void UDRRPassiveActComponent::CreateAuto(ADRREffectUnitBase* Effect)
{
	DRROnAutoEffect* OnAutoTemp = new DRROnAutoEffect(Effect);
	AutoEffects.Add(OnAutoTemp);
	OnAutoTemp->BeginEffect(GetOwner());
}

void UDRRPassiveActComponent::CreateHit(ADRREffectUnitBase* Effect)
{
	DRROnHitEffect* OnHitTemp = new DRROnHitEffect(Effect);
	HittedEffects.Add(OnHitTemp);
	OnHitTemp->BeginEffect(GetOwner());
}

void UDRRPassiveActComponent::CreateDamage(ADRREffectUnitBase* Effect)
{
	DRROnDamageEffect* OnDamageTemp = new DRROnDamageEffect(Effect);
	DamagedEffects.Add(OnDamageTemp);
	OnDamageTemp->BeginEffect(GetOwner());

}

void UDRRPassiveActComponent::CreateAttack(ADRREffectUnitBase* Effect)
{
	DRROnAttackEffect* OnAttackTemp = new DRROnAttackEffect(Effect);
	AttackEffects.Add(OnAttackTemp);
	OnAttackTemp->BeginEffect(GetOwner());
}

