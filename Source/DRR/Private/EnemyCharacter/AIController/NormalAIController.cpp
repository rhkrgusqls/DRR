// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/AIController/NormalAIController.h"
#include "CharacterBase/CharacterBase.h"
#include "DRR.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyCharacter/EnemyCharacterBase/EnemyCharacterBase.h"
#include "PlayerCharacter/PlayerCharacterBase/PlayerCharacterBase.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Hearing.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "GameManager/EnemyManager.h"

void ANormalAIController::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AEnemyCharacterBase>(GetPawn());
	if (Character)
	{
		Agent = Character;
	}

}

ANormalAIController::ANormalAIController(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Game/Blueprints/AI/Normal/BBNormalMelee.BBNormalMelee"));
	if (BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Game/Blueprints/AI/Normal/BTNormalMeleeAI.BTNormalMeleeAI"));
	if (BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
	//AIPerceptionComponentFriendly = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionCompFriendly"));

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	/*
	FriendIdentificationSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Friendly Sight Config"));

	FriendIdentificationSight->SightRadius = 800.0f;
	FriendIdentificationSight->LoseSightRadius = Sight->SightRadius + 500.0f;
	FriendIdentificationSight->PeripheralVisionAngleDegrees = 180.0f;
	FriendIdentificationSight->DetectionByAffiliation.bDetectNeutrals = true;
	FriendIdentificationSight->SetMaxAge(10.0f);
	//Sight->AutoSuccessRangeFromLastSeenLocation = 900.0f;
	FriendIdentificationSight->DetectionByAffiliation.bDetectEnemies = true;
	FriendIdentificationSight->DetectionByAffiliation.bDetectFriendlies = true;
	*/
	Sight->SightRadius = 800.0f;
	Sight->LoseSightRadius = Sight->SightRadius + 500.0f;
	Sight->PeripheralVisionAngleDegrees = 60.0f;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Sight->SetMaxAge(10.0f);
	//Sight->AutoSuccessRangeFromLastSeenLocation = 900.0f;
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerceptionComponent->ConfigureSense(*Sight);
	//AIPerceptionComponent->SetDominantSense(Sight->GetSenseImplementation());


	//AIPerceptionComponent->ConfigureSense(*FriendIdentificationSight);
	//AIPerceptionComponentFriendly->SetDominantSense(FriendIdentificationSight->GetSenseImplementation());


	Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));

	Hearing->HearingRange = 800.0f;
	Hearing->LoSHearingRange = 1200.0f;
	AIPerceptionComponent->ConfigureSense(*Hearing);
}

//** AI Casted Player -kwakhyunbin
void ANormalAIController::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{
	
	UWorld* World = GetWorld();
	EnemyCharacter = Cast<APlayerCharacterBase>(Actor);
	if (EnemyCharacter != nullptr)
	{
		BlackboardComp->SetValueAsBool("IsTargetLookOn", true);
		BlackboardComp->SetValueAsObject("Target", Actor);
		UE_LOG(LogTemp, Warning, TEXT("Casted:%s"), *EnemyCharacter->GetName());
		return;
	}
	CastedCharacter = Cast<AEnemyCharacterBase>(Actor);
	if (CastedCharacter != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Casted:%s"), *CastedCharacter->GetName());
		if (World != nullptr)
		{
			for (TActorIterator<AEnemyManager> It(World); It; ++It)
			{
				Manager = *It;
				Manager->SetGroupNum(Character->GetEnemyCharacterNum(), CastedCharacter->GetEnemyCharacterNum());
			}
		}
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Caste"));

	
}
/*
void ANormalAIController::CheckColleagueGroup(AActor* Actor, FAIStimulus Stimulus)
{

}*/

void ANormalAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ANormalAIController::OnPerception);
	//AIPerceptionComponentFriendly->OnTargetPerceptionUpdated.AddDynamic(this, &ANormalAIController::CheckColleagueGroup);
	RunAI();
}

void ANormalAIController::RunAI()
{
	UBlackboardComponent* BlackBoardPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackBoardPtr))
	{
		Blackboard->SetValueAsVector(TEXT("StartPoint"), GetPawn()->GetActorLocation());

		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
	BlackboardComp = GetBlackboardComponent();
	BlackboardComp->SetValueAsBool("IsTargetLookOn", false);
	BlackboardComp->SetValueAsEnum("BattleState", 0);
	BlackboardComp->SetValueAsVector("StartPoint",GetPawn()->GetActorLocation());
}

void ANormalAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}
