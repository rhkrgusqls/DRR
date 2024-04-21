// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DRRCharacterWidgetInterface.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnHPZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHPChangedDelegate, float CurrentHP);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMPChangedDelegate, float CurrentMP);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSTChangedDelegate, float CurrentST);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGoldChangedDelegate, float CurrentGold);
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDRRCharacterWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DRR_API IDRRCharacterWidgetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetupCharacterWidget(class UDRRUserWidget* InUserWidget) = 0;
};
