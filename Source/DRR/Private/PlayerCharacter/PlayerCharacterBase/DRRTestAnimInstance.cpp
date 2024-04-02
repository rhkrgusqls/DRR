// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/PlayerCharacterBase/DRRTestAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UDRRTestAnimInstance::UDRRTestAnimInstance()
{
	MoveThreadshold = 3.0f;
	JumpThreadshold = 100.0f;
}

void UDRRTestAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UDRRTestAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		GroundSpeed = Movement->Velocity.Size2D();
		bIsIdle = GroundSpeed < MoveThreadshold;

		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Movement->Velocity.Z > JumpThreadshold);
	}
}
