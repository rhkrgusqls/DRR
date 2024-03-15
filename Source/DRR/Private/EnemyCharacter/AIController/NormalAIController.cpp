// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/AIController/NormalAIController.h"
#include "CharacterBase/CharacterBase.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"

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

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	Sight->SightRadius = 2000.0f;
	Sight->LoseSightRadius = Sight->SightRadius + 500.0f;
	Sight->PeripheralVisionAngleDegrees = 90.0f;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerceptionComponent->ConfigureSense(*Sight);
	AIPerceptionComponent->SetDominantSense(Sight->GetSenseImplementation());
}

void ANormalAIController::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{
	EnemyCharacter = Cast<ACharacterBase>(Actor);
	if (EnemyCharacter == nullptr)
	{
		return;
	}
	
}

void ANormalAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ANormalAIController::OnPerception);
}
