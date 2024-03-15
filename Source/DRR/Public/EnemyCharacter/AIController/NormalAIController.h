// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "AIController.h"
#include "NormalAIController.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ANormalAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
public:
	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent;

	virtual void BeginPlay();

public:
	ANormalAIController(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadWrite)
	class ACharacterBase* Agent;

	ACharacterBase* Character;
	ACharacterBase* EnemyCharacter;

	UFUNCTION()
	void OnPerception(AActor* Actor, FAIStimulus Stimulus);

	class UAISenseConfig_Sight* Sight;

	virtual void OnPossess(APawn* InPawn) override;

};
