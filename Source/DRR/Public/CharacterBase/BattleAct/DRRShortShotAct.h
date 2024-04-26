// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase/BattleAct/DRRAct.h"

/**
 * 
 */
class DRR_API DRRShortShotAct : public DRRAct
{
public:


	DRRShortShotAct() ;
	virtual bool BeginAct() override;
	virtual bool NextReset() override;
	virtual float GetNextTime() override;


protected:
	virtual bool AfterAct() override;
	
protected:


};

