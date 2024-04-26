// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase/BattleAct/DRRAct.h"

/**
 * 
 */
class DRR_API DRRComboAct : public DRRAct
{
public:

	DRRComboAct();
	virtual bool BeginAct() override;
	virtual bool NextReset() override;
	virtual FName GetMontgeSectionName() override;
protected:
	virtual bool AfterAct() override;
	
protected:

};

