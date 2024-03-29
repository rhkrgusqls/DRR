// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/DRRActableInterface.h"

DECLARE_DELEGATE(FActionDelegate);
/**
 * 
 */
class DRR_API DRRAct
{
public:

	DRRAct();
	void SetActor(class IDRRActableInterface* Target);
	virtual void ActRelease();
	const class UDA_ActData* GetCurAct();
	virtual bool AfterAct();
	~DRRAct();
	virtual float GetNextTime();
	virtual uint8 NextAct();
	virtual bool NextReset();
	FOnActFuncDelegate DoBeginAct();
	FOnActFuncDelegate DoAct();
	FOnActFuncDelegate DoEndAct();
	virtual bool BeginAct();
	virtual FName GetMontgeSectionName();
	virtual void EndAct();
protected:
	
private:
	void SetActs(class IDRRActableInterface* Target);

protected:

	FOnActFuncDelegate BeginActFunc;
	FOnActFuncDelegate EndActFunc;
	TArray<FOnActFuncDelegate> ActFunc;
	uint8 curActCount;
	uint8 curFuncCount;
	TObjectPtr<class UDA_ActData> CurAct;
	

};


