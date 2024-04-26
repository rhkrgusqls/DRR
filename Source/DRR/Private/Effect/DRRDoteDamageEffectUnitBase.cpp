// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/DRRDoteDamageEffectUnitBase.h"
#include "CharacterBase/CharacterBase.h"
#include "Utilities/UtilityList.h"

void ADRRDoteDamageEffectUnitBase::UpdateFunc(AActor* target)
{
	ACharacterBase* Temp = Cast<ACharacterBase>(target);
	Temp->ReciveAttack(10.0f);
	
}
