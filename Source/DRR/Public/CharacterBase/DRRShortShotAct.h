// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRRAct.h"

#include "DRRShortShotAct.generated.h"
/**
 * 
 */
UCLASS()
class DRR_API UDRRShortShotAct : public UDRRAct
{
public:
	GENERATED_BODY()


	UDRRShortShotAct() ;
	virtual bool BeginAct() override;
	virtual bool NextReset() override;
	virtual float GetNextTime() override;


protected:
	virtual void EndAct() override;
	virtual bool AfterAct() override;
	
protected:


};

