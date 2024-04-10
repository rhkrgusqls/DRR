// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/PlayerCharacterBase/PlayerCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter/PlayerCharacterBase/PlayerControlDataAsset.h"
#include "CharacterBase/CharacterBase.h"
#include "Components/CapsuleComponent.h" 
#include "Animation/PlayerAnim/DRRAnimInstance.h"
#include "Item/ABWeaponItem.h"

#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

APlayerCharacterBase::APlayerCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Capsule
	GetCapsuleComponent()->InitCapsuleSize(40.0f, 100.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	// Set Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	//Set Movement Default
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	//Set Rotation Remit
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//Set Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Game/Asset/Character/Meshes/Player.Player"));

	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
		GetMesh()->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	}

	

	//SetInputDataAsset
	static ConstructorHelpers::FObjectFinder<UPlayerControlDataAsset> QuaterDataAssetRef(TEXT("/Game/Asset/Character/CharacterControlData/DA_CCQuater.DA_CCQuater"));
	if (QuaterDataAssetRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::Quater, QuaterDataAssetRef.Object);
	}

	//Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/Blueprints/Animation/ABP_PlayerAnim.ABP_PlayerAnim_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	/*---------------------------------------------------*/

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Camera Boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 350.0f;
	CameraBoom->bUsePawnControlRotation = true;
	//Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;

	//Input
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionQuaterMoveRef(TEXT("/Game/Asset/Character/CharacterControlData/Action/IA_QuaterMove.IA_QuaterMove"));
	if (InputActionQuaterMoveRef.Object)
	{
		QuaterMoveAction = InputActionQuaterMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Game/Asset/Character/CharacterControlData/Action/IA_Jump.IA_Jump"));
	if (InputActionJumpRef.Object)
	{
		JumpAction = InputActionJumpRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionSitRef(TEXT("/Game/Asset/Character/CharacterControlData/Action/IA_Sit.IA_Sit"));
	if (InputActionSitRef.Object)
	{
		SitAction = InputActionSitRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionAttackRef(TEXT("/Game/Asset/Character/CharacterControlData/Action/IA_Attack.IA_Attack"));
	if (InputActionJumpRef.Object)
	{		
		AttackAction = InputActionAttackRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionChangeRef(TEXT("/Game/Asset/Character/CharacterControlData/Action/IA_Change.IA_Change"));
	if (InputActionJumpRef.Object)
	{
		weaponChangeAction = InputActionChangeRef.Object;
	}

}

void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	SetCharacterControl(ECharacterControlType::Quater);

	// Weapon Mesh Component
	FName WeaponSocket(TEXT("Tumb2_R"));
	auto CurWeapon = GetWorld()->SpawnActor<AABWeaponItem>(FVector::ZeroVector, FRotator::ZeroRotator);
	WeaponList[0] = CurWeapon;
	if (nullptr != CurWeapon)
	{
		CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
	}
	
}

void APlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked <UEnhancedInputComponent>(PlayerInputComponent);	
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(QuaterMoveAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::QuaterMove);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerCharacterBase::Attack);
	EnhancedInputComponent->BindAction(SitAction, ETriggerEvent::Started, this, &APlayerCharacterBase::Sit);
	EnhancedInputComponent->BindAction(weaponChangeAction, ETriggerEvent::Started, this, &APlayerCharacterBase::weaponChange);
}

void APlayerCharacterBase::SetCharacterControlData(const UPlayerControlDataAsset* CharacterControlData)
{
	Super::SetCharacterControlData(CharacterControlData);

	//Input
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (nullptr != Subsystem)
	{
		Subsystem->ClearAllMappings();
		if (CharacterControlData->InputMappingContext)
		{
			Subsystem->AddMappingContext(CharacterControlData->InputMappingContext, 0);
		}
		//Subsystem->RemoveMappingContext(DefaultMappingContext);
	}

	//Camera
	CameraBoom->TargetArmLength = CharacterControlData->TargetArmLength;
	CameraBoom->SetRelativeRotation(CharacterControlData->RelativeRotation);
	CameraBoom->bUsePawnControlRotation = CharacterControlData->bUsePawnControlRotation;
	CameraBoom->bDoCollisionTest = CharacterControlData->bDoCollisionTest;
	CameraBoom->bInheritPitch = CharacterControlData->bInheritPitch;
	CameraBoom->bInheritYaw = CharacterControlData->bInheritYaw;
	CameraBoom->bInheritRoll = CharacterControlData->bInheritRoll;
}

void APlayerCharacterBase::EquipWeapon(UABItemData* InItemData)
{
	UE_LOG(LogTemp, Log, TEXT("EquipWeapon"));
	
	
}

void APlayerCharacterBase::QuaterMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	float MovementVectorsizeSquared = MovementVector.SquaredLength();
	if (MovementVectorsizeSquared > 1.0f)
	{
		//크기를 1로 고정
		MovementVector.Normalize();
		MovementVectorsizeSquared = 1.0f;
	}
	else {}

	FVector MoveDirection = FVector(MovementVector.X, MovementVector.Y, 0.0f);
	GetController()->SetControlRotation(FRotationMatrix::MakeFromX(MoveDirection).Rotator());
	AddMovementInput(MoveDirection, MovementVectorsizeSquared);
}

void APlayerCharacterBase::Attack(const FInputActionValue& Value) {
	UE_LOG(LogTemp, Log, TEXT("Attack"));
}

void APlayerCharacterBase::Sit(const FInputActionValue& Value) {
	
	if (IsSit == true ) {
		IsSit = false;		
		UnCrouch();
	}
	
	else if (IsSit == false) {
		IsSit = true;		
		Crouch();
	}	
}

//Change weapon
void APlayerCharacterBase::weaponChange(const FInputActionValue& Value) {
	AABWeaponItem* Weapon;
	Weapon->Change();
}


void APlayerCharacterBase::SetCharacterControl(ECharacterControlType ControlType)
{
	UPlayerControlDataAsset* NewCharacterControlData = CharacterControlManager[ControlType];
	SetCharacterControlData(NewCharacterControlData);
}
