// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "PlayerCharacter/PlayerCharacterBase/PlayerControlDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Effect/DRRAutomaticRecoveryEffect.h"

#include "CharacterBase/DRRActComponent.h"
#include "CharacterBase/DRRPassiveActComponent.h"
#include "Utilities/UtilityList.h"
#include "Physics/PhysicsInterfacePhysX.h"
#include "PhysicsEngine/PhysicsAsset.h"
#include "PhysicsEngine/PhysicsConstraintTemplate.h"
#include "PhysicsEngine/ConstraintTypes.h"
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
	if (bIsDead)
	{
		return;
	}
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
	


	AController* CurrentController = GetController();

	if (CurrentController)
	{
		CurrentController->UnPossess();
	}
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();

	if (MovementComponent)
	{
		MovementComponent->StopMovementImmediately();
		MovementComponent->DisableMovement();
	}
	GetWorldTimerManager().SetTimer(DeathTimer, this, &ACharacterBase::DestroySelf, 5.0f, false);

	USkeletalMeshComponent* TempMesh = GetMesh();
	if (TempMesh)
	{
		TempMesh->SetSimulatePhysics(true);
		TempMesh->SetAllBodiesSimulatePhysics(true);
		TempMesh->SetCollisionProfileName(TEXT("Ragdoll"));

		UPhysicsAsset* TempPhysicsAsset = TempMesh->GetPhysicsAsset();
		if (TempPhysicsAsset)
		{

			for (UPhysicsConstraintTemplate* TempConstraintTemplate : TempPhysicsAsset->ConstraintSetup)
			{
				if (TempConstraintTemplate)
				{

					FConstraintInstance& TempConstraintInstance = TempConstraintTemplate->DefaultInstance;
					TempConstraintInstance.SetLinearLimits(ELinearConstraintMotion::LCM_Free, ELinearConstraintMotion::LCM_Free, ELinearConstraintMotion::LCM_Free, 0.0f);

				}
			}
		}
	}

	UCapsuleComponent* TempCapsule = GetCapsuleComponent();
	if (TempCapsule)
	{
		TempCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if (TempMesh && TempCapsule)
	{
		TempMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}

void ACharacterBase::DestroySelf()
{
	Destroy();
}
