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

// Called when the game starts or when spawned
void ADRRWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	FirstActRef = Cast<ADRRActUnitBase>(GetWorld()->SpawnActor(FirstAct));
	SecondActRef = Cast<ADRRActUnitBase>(GetWorld()->SpawnActor(SecondAct));

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, false);
	FirstActRef->AttachToActor(this, AttachmentRules);
	SecondActRef->AttachToActor(this, AttachmentRules);
	
}



