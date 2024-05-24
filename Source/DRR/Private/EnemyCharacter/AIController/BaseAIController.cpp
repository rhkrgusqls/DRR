
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

// Called when the game starts
void ABaseAIController::BeginPlay()
{
    Super::BeginPlay();
    Character = Cast<AEnemyCharacterBase>(GetPawn());
    if (Character)
    {
        Agent = Character;
    }
}

// Constructor for the AI Controller
ABaseAIController::ABaseAIController(const FObjectInitializer& ObjectInitializer)
{
    // Find and set Blackboard Data and Behavior Tree
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

    // Create Perception and Sense Configurations
    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));

    // Sight Sense Configuration
    Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
    Sight->SightRadius = 800.0f;
    Sight->LoseSightRadius = Sight->SightRadius + 500.0f;
    Sight->PeripheralVisionAngleDegrees = 60.0f;
    Sight->DetectionByAffiliation.bDetectNeutrals = true;
    Sight->SetMaxAge(10.0f);
    Sight->DetectionByAffiliation.bDetectEnemies = true;
    Sight->DetectionByAffiliation.bDetectFriendlies = true;

    AIPerceptionComponent->ConfigureSense(*Sight);

    // Hearing Sense Configuration
    Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
    Hearing->HearingRange = 800.0f;
    //Hearing->LoSHearingRange = 1200.0f;
    Hearing->DetectionByAffiliation.bDetectNeutrals = true;
    Hearing->SetMaxAge(10.0f);
    Hearing->DetectionByAffiliation.bDetectEnemies = true;
    Hearing->DetectionByAffiliation.bDetectFriendlies = true;

    AIPerceptionComponent->ConfigureSense(*Hearing);
}

// Callback function for perception events
void ABaseAIController::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{
    float LastPerceivedTime = GetWorld()->GetTimeSeconds();
    UWorld* World = GetWorld();
    EnemyCharacter = Cast<APlayerCharacterBase>(Actor);
    FName STag = Stimulus.Tag;
   // Character = GetPawn();
        // Handle noise perception
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
            // Handle player character perception
            if (EnemyCharacter != nullptr)
            {
                // Check if the actor was successfully perceived
                if (Stimulus.WasSuccessfullySensed())
                {
                    BlackboardComp->SetValueAsBool("IsTargetLookOn", true);
                    BlackboardComp->SetValueAsObject("Target", Actor);
                    BlackboardComp->SetValueAsEnum("BattleState", 2);
                    UE_LOG(LogTemp, Warning, TEXT("Casted:%s"), *EnemyCharacter->GetName());
                    BlackboardComp->SetValueAsFloat("LastPerceivedTime", LastPerceivedTime);
                    GetWorld()->GetTimerManager().ClearTimer(FRemoveTargetTimer);
                    // Additional logic to handle the perceived actor can be added here
                }
                else
                {
                    GetWorld()->GetTimerManager().SetTimer(FRemoveTargetTimer, this, &ABaseAIController::RemoveTarget, 10.0f, false);
                }
                return;
            }
        }

    // Handle enemy character perception
    CastedCharacter = Cast<AEnemyCharacterBase>(Actor);
    if (CastedCharacter != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Casted:%s"), *CastedCharacter->GetName());
        if (World != nullptr)
        {
            for (TActorIterator<AEnemyManager> It(World); It; ++It)
            {
                Manager = *It;

                if (Character == nullptr || CastedCharacter == nullptr)
                {
                    return;
                }

                if (CastedCharacter->GetEnemyCharacterNum() == 0)
                {
                    return;
                }

                Manager->SetGroupNum(Character->GetEnemyCharacterNum(), CastedCharacter->GetEnemyCharacterNum());

                GetWorld()->GetTimerManager().ClearTimer(FRemoveGroupTimer);
               GetWorld()->GetTimerManager().SetTimer(FRemoveGroupTimer, this, &ABaseAIController::RemoveGroup, 10.0f, false);
            }
        }
        return;
    }
    UE_LOG(LogTemp, Warning, TEXT("Caste"));
}

// Called when the controller possesses a pawn
void ABaseAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseAIController::OnPerception);
    RunAI();
 
    Character = Cast<AEnemyCharacterBase>(GetPawn());
    if (Character)
    {
        Agent = Character;
    }
}

// Run the AI behavior tree
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

// Stop the AI behavior tree
void ABaseAIController::StopAI()
{
    UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
    if (BTComponent)
    {
        BTComponent->StopTree();
    }
}

// Remove the target from the blackboard
void ABaseAIController::RemoveTarget()
{
    BlackboardComp->SetValueAsBool("IsTargetLookOn", false);
    BlackboardComp->ClearValue("Target");
    BlackboardComp->SetValueAsEnum("BattleState", 0);
    BlackboardComp->SetValueAsFloat("LastPerceivedTime", 0.0f);
}

// Called when a blackboard value changes
void ABaseAIController::OnBlackboardValueChanged(FName KeyName)
{
    if (KeyName == TEXT("MyBlackboardKey"))
    {
        // Add logic to handle blackboard value changes here
    }
}

// Restart the behavior tree
void ABaseAIController::RestartBehaviorTree()
{
    RunBehaviorTree(BTAsset);
}

void ABaseAIController::RemoveGroup()
{
    Manager->NullGroup(Character->GetEnemyCharacterNum());
}
