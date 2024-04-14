// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "PlayerCharacter/PlayerCharacterBase/PlayerControlDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"


#include "CharacterBase/DRRActComponent.h"
// Sets default values
ACharacterBase::ACharacterBase()
{
	
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	
}

void ACharacterBase::ActFunc()
{
	ActComponent->ActFunc();

}

void ACharacterBase::SetCharacterControlData(const UPlayerControlDataAsset* CharacterControlData)
{
	//pawn
	bUseControllerRotationPitch = CharacterControlData->bUseControlRotationPitch;
	bUseControllerRotationYaw = CharacterControlData->bUseControlRotationYaw;
	bUseControllerRotationRoll = CharacterControlData->bUseControlRotationRoll;

	//Movement
	GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement;
	GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;
}




void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HPRegenHandle++;
	if (HPRegenHandle == 9)
	{
		CurrentHP = CurrentHP + HPRegenSpeed * (MaxHP - CurrentHP) * 0.01 - DotDamage;
		HPRegenHandle = 0;
	}
}

void ACharacterBase::ReciveAttack(float physicsDamage/*, float MagicDamage*/)
{
	CurrentHP = CurrentHP - physicsDamage/ physicsDef/*-MagicDamage/MagicDef*/;
}

void ACharacterBase::SetDotDamage(float TickDamage, float DurationTime)
{
	DotDamage = DotDamage + TickDamage;

	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([this, TickDamage]() { RemoveDotDamage(TickDamage); });

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, TimerCallback, DurationTime, false);
}

void ACharacterBase::RemoveDotDamage(float TickDamage)
{
	DotDamage = DotDamage - TickDamage;
}

void ACharacterBase::RemoveDotDamage2(float TickDamage)
{
	
}

