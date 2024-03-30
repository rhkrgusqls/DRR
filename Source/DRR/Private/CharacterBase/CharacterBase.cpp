// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "PlayerCharacter/PlayerCharacterBase/PlayerControlDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/DRRWidgetComponent.h"
#include "UI/DRRUserWidget.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Capsule
	GetCapsuleComponent()->InitCapsuleSize(500.0f, 100.0f);
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
	}

	//SetInputDataAsset
	static ConstructorHelpers::FObjectFinder<UPlayerControlDataAsset> QuaterDataAssetRef(TEXT("/Game/Asset/Character/CharacterControlData/DA_CCQuater.DA_CCQuater"));
	if (QuaterDataAssetRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::Quater, QuaterDataAssetRef.Object);
	}

	//Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/Blueprints/Animation/ABP_PlayerAnim.ABP_PlayerAnim"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	// UI Widget
	PlayerHUD = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerHPBar"));

	static ConstructorHelpers::FClassFinder<UUserWidget> PlayerHUDRef(TEXT("/Game/Asset/UI/WBP_MainHUD.WBP_MainHUD_C"));
	if (PlayerHUDRef.Class)
	{
		PlayerHUD->SetWidgetClass(PlayerHUDRef.Class);
		PlayerHUD->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	//OnHPZero.AddUObject(this, &ACharacterBase::SetDead();		//Please Make SetDead() Function in this .cpp
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	SetMaxHP(100.0f);
	SetHP(MaxHP);
}

void ACharacterBase::SetupCharacterWidget(UDRRUserWidget* InUserWidget)
{
	if (InUserWidget)
	{
		InUserWidget->SetMaxHP(MaxHP);
		InUserWidget->UpdateHP(CurrentHP);
		OnHPChanged.AddUObject(InUserWidget, &UDRRUserWidget::UpdateHP);
	}
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

void ACharacterBase::SetMaxHP(float NewHP)
{
	MaxHP = FMath::Clamp(NewHP, 0.0f, 1000.0f);
}

void ACharacterBase::SetHP(float NewHP)
{
	CurrentHP = FMath::Clamp(NewHP, 0.0f, 1000.0f);

	OnHPChanged.Broadcast(CurrentHP);
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HPRegenHandle++;
	if (HPRegenHandle == 9)
	{
		CurrentHP = CurrentHP + HPRegenSpeed * (MaxHP - CurrentHP) * 0.01;
		HPRegenHandle = 0;
	}
}

float ACharacterBase::ApplyDamage(float InDamage)
{
	float ActualDamage = FMath::Clamp(InDamage, 0.0f, InDamage);

	SetHP(CurrentHP - ActualDamage);
	if (CurrentHP <= 0.0f)
	{
		// Please call Dead() (or else simillar) function in here
		OnHPZero.Broadcast();
	}

	return 0.0f;
}
