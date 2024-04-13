// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/DRRActableInterface.h"
#include "DRRAct.generated.h"
DECLARE_DELEGATE(FActionDelegate);
/**
 * 
 */
UCLASS()
class DRR_API UDRRAct :public UObject
{
public:
	GENERATED_BODY()

	UDRRAct();
	
	void SetActor(class IDRRActableInterface* Target);
	virtual void ActRelease();
	const class UDA_ActData* GetCurAct();
	//다음 행동을 위한 입력
	virtual bool AfterAct();
	~UDRRAct();
	virtual float GetNextTime();
	virtual uint8 NextAct();
	//입력에 필요성에 따른 반환.행동 체크 후 다음 행동떄 입력이 필요할지 안할지에대한 반환.
	virtual bool NextReset();
	virtual uint8 GetCurFuncCount();
	FOnActFuncDelegate DoBeginAct();
	FOnActFuncDelegate DoAct();
	FOnActFuncDelegate DoEndAct();
	//입력의 필요성에따른 반환. 단타, 콤보는 계속 입력해야 다음 행동을 하지만 차지, 캐스트는 다음 입력은 필요없고 다음 입력이 있으면 행동을 멈춘다.
	virtual bool BeginAct();
	virtual FName GetMontgeSectionName();
	virtual void EndAct();
	FOnActCheckConditionDelegate GetConditionCheckFunc() { return ConditionCheckFunc; }

protected:
	
private:
	void SetActs(class IDRRActableInterface* Target);
	virtual void BeginDestroy() override;
protected:

	FOnActFuncDelegate BeginActFunc;
	FOnActFuncDelegate EndActFunc;
	FOnActCheckConditionDelegate ConditionCheckFunc;
	TArray<FOnActFuncDelegate> ActFunc;
	uint8 curActCount;
	uint8 curFuncCount;
	TObjectPtr<class UDA_ActData> CurAct;
	

};


