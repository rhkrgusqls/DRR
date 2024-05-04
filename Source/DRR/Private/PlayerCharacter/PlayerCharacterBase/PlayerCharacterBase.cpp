// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/PlayerCharacterBase/PlayerCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter/PlayerCharacterBase/PlayerControlDataAsset.h"
#include "CharacterBase/CharacterBase.h"
#include "Components/CapsuleComponent.h" 
#include "Animation/PlayerAnim/DRRAnimInstance.h"

#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Perception/AISense.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AIPerceptionSystem.h"

#include "Interface/DRRActableInterface.h"
#include "CharacterBase/DRRActComponent.h"
#include "Equipment/Weapon/DRRWeaponBase.h"

#include "UI/DRRWidgetComponent.h"
#include "UI/DRRUserWidget.h"

#include "Kismet/GameplayStatics.h"
#include "GameManager/DRRMainGameMode.h"

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
	/*static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Game/Asset/Character/Meshes/Player.Player"));

	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
		GetMesh()->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	}*/

	//SetInputDataAsset
	static ConstructorHelpers::FObjectFinder<UPlayerControlDataAsset> QuaterDataAssetRef(TEXT("/Game/Asset/Character/CharacterControlData/DA_CCQuater.DA_CCQuater"));
	if (QuaterDataAssetRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::Quater, QuaterDataAssetRef.Object);
	}

	//Animation
	//static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/Blueprints/Animation/ABP_PlayerAnim.ABP_PlayerAnim_C"));
	//if (AnimInstanceClassRef.Class)
	//{
	//	GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	//}

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

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLeftPressRef(TEXT("/Game/Asset/Character/CharacterControlData/Action/IA_PressLeftFireAction.IA_PressLeftFireAction"));
	if (InputActionLeftPressRef.Object)
	{
		ActLeftPressAction = InputActionLeftPressRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionRightPressRef(TEXT("/Game/Asset/Character/CharacterControlData/Action/IA_PressRightFireAction.IA_PressRightFireAction"));
	if (InputActionRightPressRef.Object)
	{
		ActRightPressAction = InputActionRightPressRef.Object;
	}


	// UI Widget
	PlayerHUD = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerHUD"));
	//ActComponent = CreateDefaultSubobject<UDRRActComponent>(TEXT("Act"));

	static ConstructorHelpers::FClassFinder<UUserWidget> PlayerHUDRef(TEXT("/Game/Asset/UI/Main/WBP_MainHUD.WBP_MainHUD_C"));
	if (PlayerHUDRef.Class)
	{
		PlayerHUD->SetWidgetClass(PlayerHUDRef.Class);
		PlayerHUD->SetCollisionEnabled(ECollisionEnabled::NoCollision);		
	}

	//OnHPZero.AddUObject(this, &ACharacterBase::SetDead();		//Please Make SetDead() Function in this .cpp
}

void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	SetCharacterControl(ECharacterControlType::Quater);

	SetMaxHP(100.0f);
	SetHP(MaxHP);

	SetMaxMP(100.0f);
	SetMP(MaxMP);

	SetMaxST(100.0f);
	SetST(MaxST);

	SetMaxGold(999999);
	SetGold(0);

	//ADRRMainGameMode* MyMode = Cast<ADRRMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	//HUDWidget = Cast<UDRRUserWidget>(MyMode->GetMainHUDWidget());

	//SetupCharacterWidget(HUDWidget);
}

AActor* HitedActor;
void APlayerCharacterBase::Tick(float DeltaTime)
{		
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();
	if (World)
	{

		FCollisionQueryParams QueryParams;
		QueryParams.bTraceComplex = true;
		QueryParams.AddIgnoredActor(this);

		FHitResult OutHitResult;

		bool bHit = World->LineTraceSingleByChannel(
			OutHitResult,
			FollowCamera->GetComponentLocation(),
			this->GetActorLocation(),
			ECC_Visibility,
			QueryParams
		);

	SetupCharacterWidget(HUDWidget);
	if (Weapon != nullptr)
	{
		WeaponRef = GetWorld()->SpawnActor<ADRRWeaponBase>(Weapon);
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, false);
		WeaponRef->AttachToActor(this, AttachmentRules);
	}
}

}

void APlayerCharacterBase::SetupCharacterWidget(UDRRUserWidget* InUserWidget)
{
	if (InUserWidget)
	{
		InUserWidget->SetMaxHP(MaxHP);
		InUserWidget->UpdateHP(CurrentHP);
		OnHPChanged.AddUObject(InUserWidget, &UDRRUserWidget::UpdateHP);

		InUserWidget->SetMaxMP(MaxMP);
		InUserWidget->UpdateMP(CurrentMP);
		OnMPChanged.AddUObject(InUserWidget, &UDRRUserWidget::UpdateMP);

		InUserWidget->SetMaxST(MaxST);
		InUserWidget->UpdateST(CurrentST);
		OnSTChanged.AddUObject(InUserWidget, &UDRRUserWidget::UpdateST);
		
		InUserWidget->GetGoldAmount()->SetText(FText::AsNumber(CurrentGold));
		InUserWidget->UpdateGold(CurrentGold);
		//OnGoldChanged.AddUObject(InUserWidget, &UDRRUserWidget::UpdateGold);		<-AddUObject makes error and I don't know why
	}
}

void APlayerCharacterBase::SetMaxHP(float NewHP)
{
	MaxHP = FMath::Clamp(NewHP, 0.0f, 1000.0f);
}

void APlayerCharacterBase::SetHP(float NewHP)
{
	CurrentHP = FMath::Clamp(NewHP, 0.0f, 1000.0f);

	OnHPChanged.Broadcast(CurrentHP);
}

void APlayerCharacterBase::SetMaxMP(float NewMP)
{
	MaxMP = FMath::Clamp(NewMP, 0.0f, 1000.0f);
}

void APlayerCharacterBase::SetMP(float NewMP)
{
	CurrentMP = FMath::Clamp(NewMP, 0.0f, 1000.0f);
	OnMPChanged.Broadcast(CurrentMP);
}

void APlayerCharacterBase::SetMaxST(float NewST)
{
	MaxST = FMath::Clamp(NewST, 0.0f, 1000.0f);
}

void APlayerCharacterBase::SetST(float NewST)
{
	CurrentST = FMath::Clamp(NewST, 0.0f, 1000.0f);
	OnSTChanged.Broadcast(CurrentST);
}

void APlayerCharacterBase::SetMaxGold(int NewGold)
{
	MaxGold = FMath::Clamp(NewGold, 0, 999999);
}

void APlayerCharacterBase::SetGold(int NewGold)
{
	CurrentGold = FMath::Clamp(NewGold, 0, 999999);
	OnGoldChanged.Broadcast(CurrentGold);
}

//Key Input
void APlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked <UEnhancedInputComponent>(PlayerInputComponent);	
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(QuaterMoveAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::QuaterMove);
	EnhancedInputComponent->BindAction(ActLeftPressAction, ETriggerEvent::Started, this, &APlayerCharacterBase::WeaponLeftAttackPress);
	EnhancedInputComponent->BindAction(ActLeftPressAction, ETriggerEvent::Completed, this, &APlayerCharacterBase::WeaponLeftAttackRelaease);
	EnhancedInputComponent->BindAction(ActRightPressAction, ETriggerEvent::Started, this, &APlayerCharacterBase::WeaponRightAttackPress);
	EnhancedInputComponent->BindAction(ActRightPressAction, ETriggerEvent::Completed , this, &APlayerCharacterBase::WeaponRightAttackRelaease);
	EnhancedInputComponent->BindAction(SitAction, ETriggerEvent::Started, this, &APlayerCharacterBase::Sit);
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
	FName Tag = ("Noise");
	UAISense_Hearing::ReportNoiseEvent(GetWorld(), this->GetActorLocation(), 1.0f, this, 0.0f, Tag);
	AddMovementInput(MoveDirection, MovementVectorsizeSquared);
}

//Attack Type
void APlayerCharacterBase::WeaponLeftAttackPress(const FInputActionValue& Value)
{
	if (Weapon == nullptr||WeaponRef==nullptr)
	{
		return;
	}

	IDRRActableInterface* Temp = WeaponRef->GetFirstAct();
	if (Temp)
	{

		ActComponent->Act(Temp);
	}
}

void APlayerCharacterBase::WeaponRightAttackPress(const FInputActionValue& Value)
{
	if (Weapon == nullptr || WeaponRef == nullptr)
	{
		return;
	}

	IDRRActableInterface* Temp = WeaponRef->GetSecondAct();
	if (Temp)
	{

		ActComponent->Act(Temp);
	}
}

void APlayerCharacterBase::WeaponLeftAttackRelaease(const FInputActionValue& Value)
{
	if (Weapon == nullptr || WeaponRef == nullptr)
	{
		return;
	}

	IDRRActableInterface* Temp = WeaponRef->GetFirstAct();
	if (Temp)
	{

		ActComponent->ActRelease(Temp);
	}
}

void APlayerCharacterBase::WeaponRightAttackRelaease(const FInputActionValue& Value)
{
	if (Weapon == nullptr || WeaponRef == nullptr)
	{
		return;
	}

	IDRRActableInterface* Temp = WeaponRef->GetSecondAct();
	if (Temp)
	{

		ActComponent->ActRelease(Temp);
	}
}

//ETC Action
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

void APlayerCharacterBase::SetCharacterControl(ECharacterControlType ControlType)
{
	UPlayerControlDataAsset* NewCharacterControlData = CharacterControlManager[ControlType];
	SetCharacterControlData(NewCharacterControlData);
}


//float APlayerCharacterBase::ApplyDamage(float InDamage)
//{
//	float ActualDamage = FMath::Clamp(InDamage, 0.0f, InDamage);
//
//	SetHP(CurrentHP - ActualDamage);
//	if (CurrentHP <= 0.0f)
//	{
//		// Please call Dead() (or else simillar) function in here
//		OnHPZero.Broadcast();
//	}
//
//	return 0.0f;
//}
