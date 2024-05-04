// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/DRRDoteHealEffectUnitBase.h"
#include "CharacterBase/CharacterBase.h"
#include "Utilities/UtilityList.h"


void ADRRDoteHealEffectUnitBase::UpdateFunc(AActor* target)
{
	CLog::Log("Healing");
	ACharacterBase* Temp = Cast<ACharacterBase>(target);
	Temp->ReciveRecovery(10.0f);
}
