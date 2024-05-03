// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/DRRBuffEffectUnitBase.h"
#include "CharacterBase/CharacterBase.h"
#include "DataAsset/DA_StatusData.h"
#include "Utilities/UtilityList.h"

void ADRRBuffEffectUnitBase::BeginFunc(AActor* target)
{
	AddStatus(target, 1.0f);
	
}

void ADRRBuffEffectUnitBase::EndFunc(AActor* target)
{
	AddStatus(target, -1.0f);
}

void ADRRBuffEffectUnitBase::AddStatus(AActor* target,float Mul)
{

	ACharacterBase* Temp = Cast<ACharacterBase>(target);
	Temp->MaxHP += StatusData->MaxHP * Mul;
	Temp->MaxMP += StatusData->MaxMP * Mul;
	Temp->MaxST += StatusData->MaxST * Mul;
	Temp->physicsAttack += StatusData->physicsAttack * Mul;
	Temp->physicsDef += StatusData->physicsDef * Mul;
	Temp->SprintSpeed += StatusData->SprintSpeed * Mul;
	Temp->WalkSpeed += StatusData->WalkSpeed * Mul;
	Temp->HPRegenSpeed += StatusData->HPRegenSpeed * Mul;

}
