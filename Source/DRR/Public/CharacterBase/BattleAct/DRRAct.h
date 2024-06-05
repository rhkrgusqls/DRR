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
	IDRRActableInterface* GetActor() { return Actor; }
	virtual void ActRelease();
	const class UDA_ActData* GetCurAct();
	//���� �ൿ�� ���� �Է�
	virtual bool AfterAct();
	~DRRAct();
	virtual float GetNextTime();
	virtual uint8 NextAct();
	//�Է¿� �ʿ伺�� ���� ��ȯ.�ൿ üũ �� ���� �ൿ�� �Է��� �ʿ����� ������������ ��ȯ.
	virtual bool NextReset();
	virtual uint8 GetCurFuncCount();
	void DoBeginAct(AActor* User);
	FOnActFuncDelegate DoAct();
	void DoEndAct(AActor* User);
	//�Է��� �ʿ伺������ ��ȯ. ��Ÿ, �޺��� ��� �Է��ؾ� ���� �ൿ�� ������ ����, ĳ��Ʈ�� ���� �Է��� �ʿ���� ���� �Է��� ������ �ൿ�� �����.
	virtual bool BeginAct();
	virtual FName GetMontgeSectionName();
	virtual void EndAct();
	class IDRRActableInterface* GetConditionCheckFunc() { return Actor->IsAchieveCondition(threshold); }

	void IncreaseThreshold();

	float CheckManaCost();
	float CheckStaminaCost();

protected:
	bool IsLastNumAct();
	
private:
	void SetActs(class IDRRActableInterface* Target);

protected:
	class IDRRActableInterface* Actor;
	TArray<FOnActFuncDelegate> ActFunc;
	uint8 curActCount;
	uint8 curFuncCount;
	TObjectPtr<class UDA_ActData> CurAct;
	float threshold;

};


