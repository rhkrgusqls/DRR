// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Capsule-Kwakhyunbin
	GetCapsuleComponent()->InitCapsuleSize(CapsuleSize, CapsuleHeight);
	GetCapsuleComponent()->SetCollisionProfileName(FName(*CapsuleProfileName));

	// Set Mesh-Kwakhyunbin
	GetMesh()->SetRelativeLocationAndRotation(MeshVector, MeshRotator);
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	//Set Movement Default-Kwakhyunbin
	GetCharacterMovement()->bOrientRotationToMovement = CharacterbOrientRotationToMovement;
	GetCharacterMovement()->RotationRate = CharacterRotationRate;
	GetCharacterMovement()->JumpZVelocity = CharacterJumpZVelocity;
	GetCharacterMovement()->AirControl = CharacterAirControl;
	GetCharacterMovement()->MaxWalkSpeed = CharacterMaxWalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = CharacterMinAnalogWalkSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = CharacterBrakingDecelerationWalking;

	//Set Rotation Remit-Kwakhyunbin
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//Set Mesh and Anim BP-Kwakhyunbin
	GetMesh()->SetSkeletalMesh(CharacterMesh);
	GetMesh()->SetAnimInstanceClass(CharacterAnimBP);
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

