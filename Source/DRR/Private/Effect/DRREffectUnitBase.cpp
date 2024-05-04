// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/DRREffectUnitBase.h"
#include "DataAsset/Item/DA_WeaponData.h"
#include "DataAsset/DA_EffectData.h"
#include "Utilities/UtilityList.h"

ADRREffectUnitBase::ADRREffectUnitBase()
{

}

void ADRREffectUnitBase::RemoveEffect()
{
	CLog::Log("RemoveEffect");
	Destroy();
}

void ADRREffectUnitBase::BeginFunc(AActor* target)
{
	CLog::Log("EffectBeginFunc");
}

void ADRREffectUnitBase::UpdateFunc( AActor* target)
{
}

void ADRREffectUnitBase::EndFunc( AActor* target)
{

	CLog::Log("EffectEndFunc");
}

