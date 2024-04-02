// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRRAct.h"
#include "DRRChargeAct.generated.h"


/**
 * 
 */
UCLASS()
class DRR_API UDRRChargeAct : public UDRRAct
{
public:
	GENERATED_BODY()

	UDRRChargeAct() ;
	virtual void ActRelease() override;
	virtual bool BeginAct() override;
	virtual bool NextReset() override;
	virtual FName GetMontgeSectionName() override;
protected:
	virtual void EndAct() override;
	virtual bool AfterAct() override;
	
protected:

};
