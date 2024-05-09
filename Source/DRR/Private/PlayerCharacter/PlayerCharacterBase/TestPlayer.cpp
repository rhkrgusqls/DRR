// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/PlayerCharacterBase/TestPlayer.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Equipment/Weapon/DRRWeaponBase.h"
#include "Skill/DRRActUnitBase.h"

#include "CharacterBase/DRRActComponent.h"

#include "Utilities/UtilityList.h"
// Sets default values
ATestPlayer::ATestPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Create Capsule-Kwakhyunbin
	GetCapsuleComponent()->InitCapsuleSize(50.0f, 100.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));


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
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Game/Player/TestAsset/Animation/Sword_And_Shield.Sword_And_Shield"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	//Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/Blueprints/Player/Test/ABP_PlayerAnimInstance.ABP_PlayerAnimInstance_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	//입력  
	//static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Player/Input/PlayerInputMappingContext.PlayerInputMappingContext'"));
	//if (InputMappingContextRef.Object)
	//{
	//	defaultMappingContext = InputMappingContextRef.Object;
	//}


	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLeftPressRef(TEXT("/Game/Player/Input/Action/PressLeftFireAction.PressLeftFireAction"));
	if (InputActionLeftPressRef.Object)
	{
		ActLeftPressAction = InputActionLeftPressRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionRightPressRef(TEXT("/Game/Player/Input/Action/PressRightFireAction.PressRightFireAction"));
	if (InputActionRightPressRef.Object)
	{
		ActRightPressAction = InputActionRightPressRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLeftReleaseRef(TEXT("/Game/Player/Input/Action/ReleaseLeftFireAction.ReleaseLeftFireAction"));
	if (InputActionLeftReleaseRef.Object)
	{
		ActLeftReleaseAction = InputActionLeftReleaseRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionRightReleaseRef(TEXT("/Game/Player/Input/Action/ReleaseRightFireAction.ReleaseRightFireAction"));
	if (InputActionRightReleaseRef.Object)
	{
		ActRightReleaseAction = InputActionRightReleaseRef.Object;
	}
	


	//추가사항3
	ActComponent = CreateDefaultSubobject<UDRRActComponent>(TEXT("Act"));

}

// Called when the game starts or when spawned
void ATestPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (GetController() != nullptr)
	{
		APlayerController* playerController = CastChecked<APlayerController>(GetController());

		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
		if (nullptr != subsystem)
		{
			//매핑 컨택스트들을 전부 제거
			subsystem->ClearAllMappings();
			if (defaultMappingContext)
			{
				//매핑 콘텍스트 컨트롤러에 연결. removeMappingContext로 지우고 다른걸 추가할 수도 있음
				subsystem->AddMappingContext(defaultMappingContext, 0);
			}

		}
	}
}

// Called every frame
void ATestPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//향상된 입력 시스템 사용
	// 입력 매핑컨텍스트에서 액션과 함수 연결

	//형변환: 최신 트랜드. CastChecked로 형변환이 제대로 됬는지 확인
	UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	enhancedInputComponent->BindAction(ActLeftPressAction, ETriggerEvent::Started, this, &ATestPlayer::WeaponLeftAttackPress);
	enhancedInputComponent->BindAction(ActLeftPressAction, ETriggerEvent::Completed, this, &ATestPlayer::WeaponLeftAttackRelaease);
	enhancedInputComponent->BindAction(ActRightPressAction, ETriggerEvent::Started, this, &ATestPlayer::WeaponRightAttackPress);
	enhancedInputComponent->BindAction(ActRightPressAction, ETriggerEvent::Completed, this, &ATestPlayer::WeaponRightAttackRelaease);

	//매핑 컨택스트를 컨트롤러와 연결해야함

}

void ATestPlayer::SetWeapon(TSubclassOf<class ADRRWeaponBase> NewWeapon)
{
	Weapon = NewWeapon;

}

void ATestPlayer::WeaponLeftAttackPress()
{
	if (Weapon == nullptr)
	{
		return;
	}

	IDRRActableInterface* Temp = Cast<ADRRWeaponBase>(Weapon->GetDefaultObject())->GetFirstAct();
	if (Temp!=nullptr)
	{

		ActComponent->Act(Temp);
	}
}

void ATestPlayer::WeaponLeftAttackRelaease()
{
	if (Weapon == nullptr)
	{
		return;
	}

	IDRRActableInterface* Temp = Cast<ADRRWeaponBase>(Weapon->GetDefaultObject())->GetFirstAct();
	if (Temp != nullptr)
	{

		ActComponent->ActRelease(Temp);
	}
}
void ATestPlayer::WeaponRightAttackPress()
{
	if (Weapon == nullptr)
	{
		return;
	}

	IDRRActableInterface* Temp = Cast<ADRRWeaponBase>(Weapon->GetDefaultObject())->GetSecondAct();
	if (Temp != nullptr)
	{

		ActComponent->Act(Temp);
	}
}

void ATestPlayer::WeaponRightAttackRelaease()
{
	if (Weapon == nullptr)
	{
		return;
	}

	IDRRActableInterface* Temp = Cast<ADRRWeaponBase>(Weapon->GetDefaultObject())->GetSecondAct();
	if (Temp != nullptr)
	{

		ActComponent->ActRelease(Temp);
	}
}

void ATestPlayer::ActFunc()
{
	ActComponent->ActFunc();
}
