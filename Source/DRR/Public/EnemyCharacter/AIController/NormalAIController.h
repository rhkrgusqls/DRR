// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "AIController.h"
#include "EnemyCharacter/EnemyCharacterBase/EnemyCharacterBase.h"
#include "NormalAIController.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ANormalAIController : public AAIController
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent;
	//UPROPERTY(VisibleAnywhere)
	//UAIPerceptionComponent* AIPerceptionComponentFriendly;
	virtual void BeginPlay();

public:
	ANormalAIController(const FObjectInitializer& ObjectInitializer);

	void RunAI();
	void StopAI();

	UPROPERTY(BlueprintReadWrite)
	class AEnemyCharacterBase* Agent;

	AEnemyCharacterBase* Character;

	AEnemyManager* Manager;

	AEnemyCharacterBase* CastedCharacter;

	AActor* EnemyCharacter;

	UFUNCTION()
	void OnPerception(AActor* Actor, FAIStimulus Stimulus);
	//UFUNCTION()
	//void CheckColleagueGroup(AActor* Actor, FAIStimulus Stimulus);

	class UAISenseConfig_Sight* Sight;
	//class UAISenseConfig_Sight* FriendIdentificationSight;

	class UAISenseConfig_Hearing* Hearing;

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;


	UBlackboardComponent* BlackboardComp;
};
