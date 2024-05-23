// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Weapon/DRRWeaponBase.h"
#include "Skill/DRRActUnitBase.h"
#include "DataAsset/Item/DA_WeaponData.h"

#include"Utilities/CLog.h"

// Sets default values
ADRRWeaponBase::ADRRWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

IDRRActableInterface* ADRRWeaponBase::GetFirstAct()
{
	CLog::Log("FirstWeaponAct");
	return Cast<IDRRActableInterface>(FirstActRef);
}

IDRRActableInterface* ADRRWeaponBase::GetSecondAct()
{
	CLog::Log("SecondWeaponAct");
	return Cast<IDRRActableInterface>(SecondActRef);
}

bool ADRRWeaponBase::UnEquip()
{
	if (FirstActRef != nullptr)
	{
		FirstActRef->ActDestroy();
	}

	if (SecondActRef != nullptr)
	{
		SecondActRef->ActDestroy();
	}
	Destroy();
	return true;
}

// Called when the game starts or when spawned
void ADRRWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, false);
	if (FirstAct != nullptr)
	{
		FirstActRef = Cast<ADRRActUnitBase>(GetWorld()->SpawnActor(FirstAct));
		FirstActRef->AttachToActor(this, AttachmentRules);

	}
	if (SecondAct != nullptr)
	{
		SecondActRef = Cast<ADRRActUnitBase>(GetWorld()->SpawnActor(SecondAct));
		SecondActRef->AttachToActor(this, AttachmentRules);

	}

	
}



