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
