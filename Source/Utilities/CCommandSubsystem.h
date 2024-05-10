// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "OnlineSubsystemUtils.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "CCommandSubsystem.generated.h"

UCLASS()
class UTILITIES_API UCCommandSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UCCommandSubsystem();
	
protected:

private:

};
