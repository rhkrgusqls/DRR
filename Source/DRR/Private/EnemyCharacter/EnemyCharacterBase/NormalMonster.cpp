// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/EnemyCharacterBase/NormalMonster.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "EnemyCharacter/Enemy/NormalEnemyData/DBNormalEnemyAnimMongtage.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PlayerCharacter/PlayerCharacterBase/ABPlayerController.h"
#include "Engine/World.h"
#include "EnemyCharacter/AIController/NormalAIController.h"
#include "GameManager/EnemyManager.h"
#include "Components/ProgressBar.h"
#include "DRR.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "DBEnemyCharacterSetting.h"
#include "Components/CapsuleComponent.h"
#include "GameManager/GameManager.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"

ANormalMonster::ANormalMonster()
{
	AIControllerClass = ANormalAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
ANormalMonster::ANormalMonster(int Type) : AEnemyCharacterBase(Type)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UDBNormalEnemyAnimMongtage> EnemyAnimAssetRef(TEXT("/Game/Blueprints/DataAsset/EnemeyData/NormalEnemyAnimMongtage.NormalEnemyAnimMongtage"));
	UDBNormalEnemyAnimMongtage* EnemyAnimAsset = nullptr;
	EnemyType = Type;
	if (EnemyAnimAssetRef.Succeeded())
	{
		EnemyAnimAsset = EnemyAnimAssetRef.Object;
	}
	if (EnemyAnimAsset)
	{
		//Iterate through the array and access individual settings
		const FEnemyAnimSet& EnemyAnim = EnemyAnimAsset->SEnemyAnim[EnemyType];

		//Access variables from the EnemyData structure
		NormalAttackMontage = EnemyAnim.NormalAttackMontage;
		EnforceAttackMontage = EnemyAnim.EnforceAttackMontage;
		ChargingAttackMontage = EnemyAnim.ChargingAttackMontage;
		KnockbackMontage = EnemyAnim.KnockbackMontage;
		StiffnessMontage = EnemyAnim.StiffnessMontage;
		DeadMontage = EnemyAnim.DeadMontage;
	}

	HPBarUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("BPBarHUD"));
	static ConstructorHelpers::FClassFinder<UUserWidget>HPBarRef(TEXT("/Game/Asset/UI/EnemyUI/Normal/WBP_HPBarNormalEnemy.WBP_HPBarNormalEnemy_C"));
	if (HPBarRef.Class)
	{
		HPBarUI->SetWidgetClass(HPBarRef.Class);;
		HPBarUI->SetupAttachment(RootComponent);

		HPBarUI->SetWidgetSpace(EWidgetSpace::Screen);

		HPBarUI->SetDrawSize(FVector2D(180.0f, 20.0f));
		HPBarUI->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		HPBarUI->SetVisibility(false);
	}


	AIControllerClass = ANormalAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
void ANormalMonster::BeginPlay()
{
    Super::BeginPlay();
    AAIController* AIController = Cast<AAIController>(GetController());

    if (AIController)
    {
        UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();

        if (BlackboardComp)
        {
            bool IsAggressive = true;
            BlackboardComp->SetValueAsBool(TEXT("IsPatrolUnit"), IsAggressive);
        }
    }

	HPPrgressBar = Cast<UProgressBar>(HPBarUI->GetWidget()->GetWidgetFromName(TEXT("HP_ProgressBar")));
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		for (TActorIterator<AEnemyManager> It(World); It; ++It)
		{
			Manager = *It;
		}
	}
	if (Manager != nullptr)
	{
		MonsterNum = Manager->SetMonsterNum(this);
	}
}

void ANormalMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (DotDamage!=0)
	{
		HPBarUI->SetVisibility(true);
		SetHPBarHiddenTimer();
	}
	if (HPPrgressBar)
	{
		HPPrgressBar->SetPercent(CurrentHP / MaxHP);
	}
}

void ANormalMonster::ReciveAttack(float physicsDamage)
{
	Super::ReciveAttack(physicsDamage);
	{
		HPBarUI->SetVisibility(true);
		SetHPBarHiddenTimer();
	}
}

void ANormalMonster::SetHPBarHiddenTimer()
{
	GetWorldTimerManager().ClearTimer(HPBarHideTimerHandle);

	GetWorldTimerManager().SetTimer(HPBarHideTimerHandle, this, &ANormalMonster::HideHPBar, 5.0f, false);
}

void ANormalMonster::IsDead()
{
	Super::IsDead();
	if (Manager)
	{
		Manager->SetDeadMonster(MonsterNum);
	}
}

void ANormalMonster::HideHPBar()
{
	if (HPBarUI)
	{
		HPBarUI->SetVisibility(false);
	}
}