// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/DRREffectUnitBase.h"
#include "DataAsset/Item/DA_WeaponData.h"
#include "DataAsset/DA_EffectData.h"

ADRREffectUnitBase::ADRREffectUnitBase()
{

}

void ADRREffectUnitBase::RemoveEffect()
{
	Destroy();
}

void ADRREffectUnitBase::BeginFunc(AActor* target)
{
}

void ADRREffectUnitBase::UpdateFunc( AActor* target)
{
}

void ADRREffectUnitBase::EndFunc( AActor* target)
{
}
