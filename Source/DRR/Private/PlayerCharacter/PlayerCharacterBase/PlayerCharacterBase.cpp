// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/PlayerCharacterBase/PlayerCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter/PlayerCharacterBase/PlayerControlDataAsset.h"
#include "CharacterBase/CharacterBase.h"
#include "Components/CapsuleComponent.h" 
#include "Animation/PlayerAnim/DRRAnimInstance.h"
#include "PlayerCharacter/PlayerCharacterBase/ABPlayerController.h"
#include "Skill/DRRActUnitBase.h"
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
#include "Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"
#include "GameManager/DRRMainGameMode.h"

#include "Net/UnrealNetwork.h"
#include"Utilities/UtilityList.h"

#include "Components/BoxComponent.h"

APlayerCharacterBase::APlayerCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->InitBoxExtent(FVector(10.0f, 10.0f, 10.0f));
	BoxComponent->SetCollisionProfileName(TEXT("Trigger"));

	BoxComponent->OnComponentHit.AddDynamic(this, &APlayerCharacterBase::OnHit);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacterBase::OnOverlapEnd);

	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetCollisionProfileName(TEXT("NoCollision"));
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
		GetMesh()->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f)); // If You want Other PawnMesh, Change FVector 1.0f
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

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionchangeRef(TEXT("/Game/Asset/Character/CharacterControlData/Action/IA_Change.IA_Change"));
	if (InputActionchangeRef.Object)
	{
		ChangeAction = InputActionchangeRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLeftPressRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Asset/Character/CharacterControlData/Action/IA_PressLeftFireAction.IA_PressLeftFireAction'"));
	if (InputActionLeftPressRef.Object)
	{
		ActLeftPressAction = InputActionLeftPressRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionRightPressRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Asset/Character/CharacterControlData/Action/IA_PressRightFireAction.IA_PressRightFireAction'"));
	if (InputActionRightPressRef.Object)
	{
		ActRightPressAction = InputActionRightPressRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> WeaponChangeUpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Asset/Character/CharacterControlData/Action/IA_WeaponChange.IA_WeaponChange'"));
	if (WeaponChangeUpRef.Object)
	{
		WeaponChangeAction = WeaponChangeUpRef.Object;
	}

	// UI Widget
	PlayerHUD = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerHUD"));
	ActComponent = CreateDefaultSubobject<UDRRActComponent>(TEXT("Act"));

	static ConstructorHelpers::FClassFinder<UUserWidget> PlayerHUDRef(TEXT("/Game/Asset/UI/WBP_MainHUD.WBP_MainHUD_C"));
	if (PlayerHUDRef.Class)
	{

		PlayerHUD->SetWidgetClass(PlayerHUDRef.Class);
		PlayerHUD->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	}

	// MainWidget
	static ConstructorHelpers::FClassFinder<UUserWidget> MainHUDWidgetRef(TEXT("/Game/Asset/UI/Main/WBP_MainHUD.WBP_MainHUD_C"));
	if (MainHUDWidgetRef.Class)
	{
		MainHUDWidgetClass = MainHUDWidgetRef.Class;
	}

	//ItemListWidget
	static ConstructorHelpers::FClassFinder<UUserWidget> ItemListUIRef(TEXT("/Game/Asset/UI/Main/WBP_ItemList.WBP_ItemList_C"));
	if (ItemListUIRef.Class)
	{
		ItemListWidgetClass = ItemListUIRef.Class;
	}

	//ItemCardWidget (used inside of ItemListWidget)
	static ConstructorHelpers::FClassFinder<UUserWidget> ItemCardRef(TEXT("/Game/Asset/UI/Main/WBP_ItemListCard.WBP_ItemListCard_C"));
	if (ItemCardRef.Class)
	{
		ItemCardWidgetClass = ItemCardRef.Class;
	}

	//OnHPZero.AddUObject(this, &ACharacterBase::SetDead();		//Please Make SetDead() Function in this .cpp
	MaxWeaponNum = 3;
}

bool APlayerCharacterBase::WeaponEquip(TSubclassOf<class ADRRWeaponBase> WeaponClass, uint8 slot)
{
	if (slot >= MaxWeaponNum)
		return false;

	if (WeaponRefs[slot] != nullptr)
		WeaponUnEquip(slot);
	if (WeaponClass != nullptr)
	{
		WeaponRefs[slot] = GetWorld()->SpawnActor<ADRRWeaponBase>(WeaponClass);
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, false);
		WeaponRefs[slot]->AttachToActor(this, AttachmentRules);
		return true;
	}

	return false;
}

bool APlayerCharacterBase::WeaponUnEquip(uint8 slot)
{
	if (slot >= MaxWeaponNum)
		return false;
	if(WeaponRefs[slot]==nullptr)
		return false;

	WeaponRefs[slot]->UnEquip();
	WeaponRefs[slot] = nullptr;

	return true;
}

void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	CDisplayLog::Log(TEXT("PlayerPawnBeginPlay"));
	AABPlayerController* PlayerController = Cast<AABPlayerController>(GetController());
	if (PlayerController != nullptr&&GetGameInstance()->GetFirstLocalPlayerController()==PlayerController)
	{
		SetCharacterControl(ECharacterControlType::Quater);
		SetHUDWidgets(PlayerController);
		HUDWidget = Cast<UDRRUserWidget>(GetMainHUDWidget());
		SetupCharacterWidget(HUDWidget);
	}
	WeaponRefs.Add(nullptr);
	WeaponRefs.Add(nullptr);
	WeaponRefs.Add(nullptr);

	FVector NewLocation = GetActorLocation() + FVector(0, 0, 500);
	BoxComponent->SetWorldLocation(NewLocation);

	//SetHUDWidgets(GetGameInstance()->GetFirstLocalPlayerController());

	SetMaxHP(100.0f);
	SetHP(MaxHP);

	SetMaxMP(100.0f);
	SetMP(MaxMP);

	SetMaxST(100.0f);
	SetST(MaxST);

	SetMaxGold(999999);
	SetGold(0);

	if (GetController() != nullptr)
	{
		/*ADRRMainGameMode* MyMode = Cast<ADRRMainGameMode>(GetWorld()->GetAuthGameMode());
		if (MyMode)
		{
			CDisplayLog::Log(TEXT("MyMode Is Valid"));
			HUDWidget = Cast<UDRRUserWidget>(MyMode->GetMainHUDWidget());
			

			SetupCharacterWidget(HUDWidget);


		}*/
		
	}
	
	SetupCharacterWidget2(HUDWidget);
}

AActor* HitedActor;
void APlayerCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetupCharacterWidget2(HUDWidget);

	if (this->GetController() != GetGameInstance()->GetFirstLocalPlayerController())
		return;

	UWorld* World = GetController()->GetWorld();
	
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

		if (bHit)
		{
			AActor* HitActor = OutHitResult.GetActor();
			bool IsWall = false;
			//CDisplayLog::Log(TEXT("%s"), *GetController()->GetName());
			TArray<UPrimitiveComponent*> Components;
			OutHitResult.GetActor()->GetComponents<UPrimitiveComponent>(Components);
			for (UPrimitiveComponent* Component : Components)
			{
				if (Component->GetCollisionProfileName() == TEXT("Wall"))
				{
					IsWall = true;
				}
			}

			if (IsWall)
			{
				if (HitActor)
				{
					HitActor->SetActorHiddenInGame(true);
					if (HitedActor != HitActor)
					{
						if (HitedActor != nullptr)
						{
							HitedActor->SetActorHiddenInGame(false);
						}
						HitedActor = HitActor;
					}
					else
					{
						return;
					}
				}
			}
			else
			{
				if (HitedActor != nullptr)
				{
					HitedActor->SetActorHiddenInGame(false);
					return;
				}
			}
		}
		else
		{
			if (HitedActor!=nullptr)
			{
				HitedActor->SetActorHiddenInGame(false);
				return;
			}
		}
	}
}

void APlayerCharacterBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		OtherActor->SetActorHiddenInGame(true);
	}
}

void APlayerCharacterBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		OtherActor->SetActorHiddenInGame(false);
	}
}


void APlayerCharacterBase::SetupCharacterWidget(UDRRUserWidget* InUserWidget)
{

	if (InUserWidget)
	{
		InUserWidget->AddToViewport();
		//CDisplayLog::Log(TEXT("UserWidget Is Valid"));
		
		//OnGoldChanged.AddUObject(InUserWidget, &UDRRUserWidget::UpdateGold);		<-AddUObject makes error and I don't know why
	}
}

void APlayerCharacterBase::SetupCharacterWidget2(UDRRUserWidget* InUserWidget)
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
	}
}

void APlayerCharacterBase::IsDead()
{

	AABPlayerController* CurrentController = Cast< AABPlayerController>(  GetController());

	Super::IsDead();

	if (CurrentController)
	{
		CurrentController->RespawnPlayer();
	}

}

void APlayerCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	CDisplayLog::Log(TEXT("Possesed"));

	SetCharacterControl(ECharacterControlType::Quater);
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

void APlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked <UEnhancedInputComponent>(PlayerInputComponent);	
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(WeaponChangeAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::ChangeWeapon);
	EnhancedInputComponent->BindAction(QuaterMoveAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::QuaterMove);
	EnhancedInputComponent->BindAction(ActLeftPressAction, ETriggerEvent::Started, this, &APlayerCharacterBase::WeaponLeftAttackPress);
	EnhancedInputComponent->BindAction(ActLeftPressAction, ETriggerEvent::Completed, this, &APlayerCharacterBase::WeaponLeftAttackRelaease);
	EnhancedInputComponent->BindAction(ActRightPressAction, ETriggerEvent::Started, this, &APlayerCharacterBase::WeaponRightAttackPress);
	EnhancedInputComponent->BindAction(ActRightPressAction, ETriggerEvent::Completed, this, &APlayerCharacterBase::WeaponRightAttackRelaease);
	EnhancedInputComponent->BindAction(SitAction, ETriggerEvent::Started, this, &APlayerCharacterBase::Sit);
	EnhancedInputComponent->BindAction(ChangeAction, ETriggerEvent::Started, this, &APlayerCharacterBase::Change);
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

void APlayerCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerCharacterBase, CurWeaponNum);
}

void APlayerCharacterBase::QuaterMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	float MovementVectorsizeSquared = MovementVector.SquaredLength();
	if (MovementVectorsizeSquared > 1.0f)
	{
		//ũ�⸦ 1�� ����
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











bool APlayerCharacterBase::ServerLeftAct_Validate()
{
	return true;
}
void APlayerCharacterBase::ServerLeftAct_Implementation()
{
	MulticastLeftAct();
}
void APlayerCharacterBase::MulticastLeftAct_Implementation()
{
	WeaponLeftAct();

}

bool APlayerCharacterBase::ServerLeftActRelease_Validate()
{
	return true;
}
void APlayerCharacterBase::ServerLeftActRelease_Implementation()
{
	MulticastLeftActRelease();
}
void APlayerCharacterBase::MulticastLeftActRelease_Implementation()
{
	WeaponLeftActRelease();

}

bool APlayerCharacterBase::ServerRightAct_Validate()
{
	return true;
}
void APlayerCharacterBase::ServerRightAct_Implementation()
{
	MulticastRightAct();
}
void APlayerCharacterBase::MulticastRightAct_Implementation()
{
	WeaponRightAct();
}

bool APlayerCharacterBase::ServerRightActRelease_Validate()
{
	return true;
}
void APlayerCharacterBase::ServerRightActRelease_Implementation()
{
	MulticastRightActRelease();
}
void APlayerCharacterBase::MulticastRightActRelease_Implementation()
{
	WeaponRightActRelease();
}



void APlayerCharacterBase::WeaponLeftAttackPress(const FInputActionValue& Value)
{

	if (WeaponRefs[CurWeaponNum] == nullptr)
	{
		return;
	}
	ServerLeftAct();

}

void APlayerCharacterBase::WeaponRightAttackPress(const FInputActionValue& Value)
{
	if (WeaponRefs[CurWeaponNum] == nullptr)
	{
		return;
	}
	ServerRightAct();
}

void APlayerCharacterBase::WeaponLeftAttackRelaease(const FInputActionValue& Value)
{
	if (WeaponRefs[CurWeaponNum] == nullptr)
	{
		return;
	}
	ServerLeftActRelease();
}

void APlayerCharacterBase::WeaponRightAttackRelaease(const FInputActionValue& Value)
{
	if ( WeaponRefs[CurWeaponNum] == nullptr)
	{
		return;
	}
	ServerRightActRelease();
}










void APlayerCharacterBase::WeaponLeftAct()
{
	ADRRActUnitBase* Temp = Cast< ADRRActUnitBase>(WeaponRefs[CurWeaponNum]->GetFirstAct());
	if (Temp)
	{
		CLog::Log("LeftPress");
		//ServerAct(Temp);
		ActComponent->Act(Temp);
	}
}

void APlayerCharacterBase::WeaponLeftActRelease()
{
	ADRRActUnitBase* Temp = Cast< ADRRActUnitBase>(WeaponRefs[CurWeaponNum]->GetFirstAct());
	if (Temp)
	{

		//ServerActRelease(Temp);
		ActComponent->ActRelease(Temp);
	}
}

void APlayerCharacterBase::WeaponRightAct()
{

	ADRRActUnitBase* Temp = Cast< ADRRActUnitBase>(WeaponRefs[CurWeaponNum]->GetSecondAct());
	if (Temp)
	{
		CLog::Log("RightPress");

		//ServerAct(Temp);
		ActComponent->Act(Temp);
	}
}

void APlayerCharacterBase::WeaponRightActRelease()
{

	ADRRActUnitBase* Temp = Cast< ADRRActUnitBase>(WeaponRefs[CurWeaponNum]->GetSecondAct());
	if (Temp)
	{

		//ServerActRelease(Temp);
		ActComponent->ActRelease(Temp);
	}
}

void APlayerCharacterBase::ChangeWeapon(const FInputActionValue& Value)
{

	if (Value.Get<float>() > 0.0f)
	{
		ServerChangeWeaponUp();
	}
	else if (Value.Get<float>() < 0.0f)
	{

		ServerChangeWeaponDown();
	}
}

void APlayerCharacterBase::ChangeWeaponUp()
{

	uint8 Temp = CurWeaponNum;
	Temp = (CurWeaponNum + MaxWeaponNum + 1) % MaxWeaponNum;
	CDisplayLog::Log(TEXT("WeaponChange : %d"), Temp);
	CurWeaponNum = Temp;
}

void APlayerCharacterBase::ChangeWeaponDown()
{
	uint8 Temp = CurWeaponNum;
	Temp = (CurWeaponNum + MaxWeaponNum - 1) % MaxWeaponNum;
	CDisplayLog::Log(TEXT("WeaponChange : %d"), Temp);
	CurWeaponNum = Temp;
}


bool APlayerCharacterBase::ServerChangeWeaponUp_Validate()
{
	
	return true;
}
void APlayerCharacterBase::ServerChangeWeaponUp_Implementation()
{
	ChangeWeaponUp();
}

bool APlayerCharacterBase::ServerChangeWeaponDown_Validate()
{

	return true;
}
void APlayerCharacterBase::ServerChangeWeaponDown_Implementation()
{
	ChangeWeaponDown();
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

void APlayerCharacterBase::Change(const FInputActionValue& Value)
{
	if (Weapon != nullptr)
	{
		WeaponRef = GetWorld()->SpawnActor<ADRRWeaponBase>(Weapon);
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, false);
		WeaponRef->AttachToActor(this, AttachmentRules);
	}
}


void APlayerCharacterBase::SetCharacterControl(ECharacterControlType ControlType)
{
	UPlayerControlDataAsset* NewCharacterControlData = CharacterControlManager[ControlType];
	SetCharacterControlData(NewCharacterControlData);
}

void APlayerCharacterBase::SetHUDWidgets(APlayerController* Player)
{
	CDisplayLog::Log(TEXT("Try SetHUDWidgets"));
	//MainHUD
	if (IsValid(MainHUDWidgetClass))
	{

		CDisplayLog::Log(TEXT("IsValid Widget"));
		MainHUDWidget = Cast<UUserWidget>(CreateWidget(Player->GetWorld(), MainHUDWidgetClass));

		if (IsValid(MainHUDWidget))
		{
			MainHUDWidget->AddToViewport();
		}
	}

	//ItemList (It will be moved to other function() when GetItem() function or else is ready)
	if (IsValid(ItemListWidgetClass))
	{
		ItemListWidget = Cast<UUserWidget>(CreateWidget(Player->GetWorld(), ItemListWidgetClass));

		if (IsValid(ItemListWidget))
		{
			// add the function of Adding this UI after the event of Item Collect

			//ItemListWidget->AddToViewport();

			// add the function of deleting this UI after 3 seconds
			//GetWorldTimerManager().SetTimer(TimerHandle, ItemListWidget, ItemListWidget->SetVisibility(ESlateVisibility::Hidden), 3.0f, false);
			// Seems it need Other Function() to use it
		}
	}

	//ItemCard (It will be moved to other function() when GetItem() function or else is ready)
	if (IsValid(ItemCardWidgetClass))
	{
		ItemCardWidget = Cast<UUserWidget>(CreateWidget(Player->GetWorld(), ItemCardWidgetClass));

		if (IsValid(ItemCardWidget))
		{
			// contents about (1) Getting the name of collected Item / (2) Getting the amount of collected Item
		}
	}


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
