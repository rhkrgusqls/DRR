// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/AIController/BaseAIController.h"
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

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AEnemyCharacterBase>(GetPawn());
	if (Character)
	{
		Agent = Character;
	}
}

ABaseAIController::ABaseAIController(const FObjectInitializer& ObjectInitializer)
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

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	Sight->SightRadius = 800.0f;
	Sight->LoseSightRadius = Sight->SightRadius + 500.0f;
	Sight->PeripheralVisionAngleDegrees = 60.0f;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Sight->SetMaxAge(10.0f);
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerceptionComponent->ConfigureSense(*Sight);

	Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));

	Hearing->HearingRange = 800.0f;
	Hearing->LoSHearingRange = 1200.0f;
	Hearing->DetectionByAffiliation.bDetectNeutrals = true;
	Hearing->SetMaxAge(10.0f);
	Hearing->DetectionByAffiliation.bDetectEnemies = true;
	Hearing->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerceptionComponent->ConfigureSense(*Hearing);
}

//** AI Casted Player -kwakhyunbin
void ABaseAIController::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{
	float LastPerceivedTime = GetWorld()->GetTimeSeconds();
	UWorld* World = GetWorld();
	EnemyCharacter = Cast<APlayerCharacterBase>(Actor);
	FName STag= Stimulus.Tag;

	if (STag == TEXT("Noise"))
	{
		if (!BlackboardComp->GetValueAsBool("IsTargetLookOn"))
		{
			BlackboardComp->SetValueAsEnum("BattleState", 1);
			Blackboard->SetValueAsVector("PatrolPoint", Stimulus.StimulusLocation);
		}
		return;
	}
	else
	{
		if (EnemyCharacter != nullptr)
		{
			// Check if the actor was perceived successfully
			if (Stimulus.WasSuccessfullySensed())
			{
				BlackboardComp->SetValueAsBool("IsTargetLookOn", true);
				BlackboardComp->SetValueAsObject("Target", Actor);
				BlackboardComp->SetValueAsEnum("BattleState", 2);
				UE_LOG(LogTemp, Warning, TEXT("Casted:%s"), *EnemyCharacter->GetName());
				BlackboardComp->SetValueAsFloat("LastPerceivedTime", LastPerceivedTime);
				GetWorld()->GetTimerManager().ClearTimer(S);
				// Additional logic to handle the perceived actor can be added here
			}
			else
			{
				GetWorld()->GetTimerManager().SetTimer(S, this, &ABaseAIController::RemoveTarget, 10.0f, false);
			}
			return;
		}

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

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseAIController::OnPerception);
	RunAI();
}

void ABaseAIController::RunAI()
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
	BlackboardComp->SetValueAsVector("StartPoint", GetPawn()->GetActorLocation());

}

void ABaseAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void ABaseAIController::RemoveTarget()
{
	BlackboardComp->SetValueAsBool("IsTargetLookOn", false);
	BlackboardComp->ClearValue("Target");
	BlackboardComp->SetValueAsEnum("BattleState", 0);
	BlackboardComp->SetValueAsFloat("LastPerceivedTime", 0.0f);
}

void ABaseAIController::OnBlackboardValueChanged(FName KeyName)
{
	if (KeyName == TEXT("MyBlackboardKey"))
	{
		
	}
}

void ABaseAIController::RestartBehaviorTree()
{
	RunBehaviorTree(BTAsset);
}