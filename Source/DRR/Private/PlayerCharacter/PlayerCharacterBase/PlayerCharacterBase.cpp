// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/PlayerCharacterBase/PlayerCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameManager/GameManager.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacterBase::APlayerCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Capsule-Kwakhyunbin
	GetCapsuleComponent()->InitCapsuleSize(500.0f, 100.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	// Set Mesh-Kwakhyunbin
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	//Set Movement Default-Kwakhyunbin
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	//Set Rotation Remit-Kwakhyunbin
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//Set Mesh and Anim BP-Kwakhyunbin
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Game/ProtoTypeAsset/Characters/Heroes/Wraith/Meshes/Wraith.Wraith"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	//Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/ProtoTypeAsset/Characters/Heroes/Wraith/Wraith_AnimBlueprint.Wraith_AnimBlueprint_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}
	
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> nputActionShoulderLookRef(TEXT("/Game/Blueprints/Character/IMC_Default.IMC_Default"));
	if (nputActionShoulderLookRef.Object)
	{
		Controller = nputActionShoulderLookRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionQuaterMoveRef(TEXT("/Game/Blueprints/Character/Actions/IA_CreateSession.IA_CreateSession"));
	if (InputActionQuaterMoveRef.Object)
	{
		QuaterMoveAction = InputActionQuaterMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionShoulderMoveRef(TEXT("/Game/Blueprints/Character/Actions/IA_FindSession.IA_FindSession"));
	if (InputActionShoulderMoveRef.Object)
	{
		ShoulderMoveAction = InputActionShoulderMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionShoulderLookRef(TEXT("/Game/Blueprints/Character/Actions/IA_Jump.IA_Jump"));
	if (InputActionShoulderLookRef.Object)
	{
		ShoulderLookAction = InputActionShoulderLookRef.Object;
	}

}


void APlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked <UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(QuaterMoveAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::CreateSession);
	EnhancedInputComponent->BindAction(ShoulderMoveAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::FindSession);
	EnhancedInputComponent->BindAction(ShoulderLookAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::Jump);
}
void APlayerCharacterBase::BeginPlay()
{
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (nullptr != Subsystem)
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(Controller, 0);
	}
}

void APlayerCharacterBase::CreateSession()
{
	if (!bQuaterMoveActionPressed)
	{
		bQuaterMoveActionPressed = true;


		UGameManager* GameInstance = Cast<UGameManager>(GetGameInstance());
		if (GameInstance)
		{
			GameInstance->CreateGameSession();
		}
	}
}

void APlayerCharacterBase::FindSession()
{
	if (!bShoulderMoveActionPressed)
	{
		bShoulderMoveActionPressed = true;


		 UGameManager* GameInstance = Cast<UGameManager>(GetGameInstance());
		if (GameInstance)
		{
			GameInstance->FindGameSessions();
		} 
	}
}

void APlayerCharacterBase::Jump()
{
	if (!bShoulderLookActionPressed)
	{
		bShoulderLookActionPressed = true;


	}
}

void APlayerCharacterBase::ReleaseQuaterMoveAction()
{
	bQuaterMoveActionPressed = false;
}

void APlayerCharacterBase::ReleaseShoulderMoveAction()
{
	bShoulderMoveActionPressed = false;
}

void APlayerCharacterBase::ReleaseShoulderLookAction()
{
	bShoulderLookActionPressed = false;
}