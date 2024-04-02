// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase/DRRAct.h"
#include "DRRTriggerAct.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UDRRTriggerAct : public UDRRAct
{
	GENERATED_BODY()

public:
	UDRRTriggerAct();
	virtual bool BeginAct() override;
	virtual bool NextReset() override;
	virtual FName GetMontgeSectionName() override;
protected:
	virtual void EndAct() override;
	virtual bool AfterAct() override;

protected:
};
