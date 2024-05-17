// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/DRRPlayerState.h"
#include "Utilities/CDisplayLog.h"
ADRRPlayerState::ADRRPlayerState()
{
	
}
void ADRRPlayerState::BeginPlay()
{
	CDisplayLog::Log(TEXT("PlayerState Valid"));
}
