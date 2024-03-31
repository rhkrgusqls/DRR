// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/AIController/NormalAIController.h"
#include "CharacterBase/CharacterBase.h"
#include "PlayerCharacter/PlayerCharacterBase/PlayerCharacterBase.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

void ANormalAIController::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ACharacterBase>(GetPawn());
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

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	Sight->SightRadius = 800.0f;
	Sight->LoseSightRadius = Sight->SightRadius + 500.0f;
	Sight->PeripheralVisionAngleDegrees = 60.0f;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Sight->SetMaxAge(10.0f);
	//Sight->AutoSuccessRangeFromLastSeenLocation = 900.0f;
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerceptionComponent->ConfigureSense(*Sight);
	AIPerceptionComponent->SetDominantSense(Sight->GetSenseImplementation());

}

//** AI Casted Player -kwakhyunbin
void ANormalAIController::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{

	EnemyCharacter = Cast<APlayerCharacterBase>(Actor);
	if (EnemyCharacter != nullptr)
	{
		BlackboardComp->SetValueAsBool("IsTargetLookOn", true);
		BlackboardComp->SetValueAsObject("Target", Actor);
		UE_LOG(LogTemp, Warning, TEXT("Casted/%s"), *EnemyCharacter->GetName());
		return;
	}
	
}

void ANormalAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ANormalAIController::OnPerception);
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
}

void ANormalAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}
