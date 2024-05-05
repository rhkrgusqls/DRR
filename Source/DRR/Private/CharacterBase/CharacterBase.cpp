// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "PlayerCharacter/PlayerCharacterBase/PlayerControlDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Effect/DRRAutomaticRecoveryEffect.h"

#include "CharacterBase/DRRActComponent.h"
#include "CharacterBase/DRRPassiveActComponent.h"
#include "Utilities/UtilityList.h"
// Sets default values
ACharacterBase::ACharacterBase()
{

	PassiveComponent = CreateDefaultSubobject<UDRRPassiveActComponent>(TEXT("Passive"));
	

}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	if (AutomaticRecovery != nullptr)
	{
		CLog::Log("AddAutomaticRecovery");
		PassiveComponent->AddEffect(AutomaticRecovery, this);
	}
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




void ACharacterBase::StartSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ACharacterBase::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
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
	if (CurrentHP <= 0)
	{
		IsDead();
	}
}

//Call Hit Event
void ACharacterBase::ReciveAttack(float physicsDamage/*, float MagicDamage*/)
{
	CurrentHP = CurrentHP - physicsDamage/ physicsDef/*-MagicDamage/MagicDef*/;
	OnHPChanged.Broadcast(CurrentHP);
}

void ACharacterBase::ReciveRecovery(float physicsDamage)
{
	CurrentHP = FMath::Min(CurrentHP + physicsDamage,MaxHP) ;
	OnHPChanged.Broadcast(CurrentHP);
}

//Call DotDamage
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

void ACharacterBase::IsDead()
{
	bIsDead = true;

	PlayAnimMontage(DeadMontage);

	//DisableCharacterMovement();

	//GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &ACharacterBase::HandleDeath, 5.0f, false);
}
