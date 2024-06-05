// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/DRRAutomaticRecoveryEffect.h"
#include "CharacterBase/CharacterBase.h"
#include "Utilities/UtilityList.h"

void ADRRAutomaticRecoveryEffect::UpdateFunc(AActor* target)
{
	CLog::Log("AutomaticHealUpdate");
	ACharacterBase* Temp = Cast<ACharacterBase>(target);
	Temp->ReciveRecovery(Temp->HPRegenSpeed);
	Temp->ReciveSTRecovery(Temp->STRegenSpeed);
	Temp->ReciveMPRecovery(Temp->MPRegenSpeed);
}
