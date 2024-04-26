// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DRREffectUnitBase.generated.h"

UCLASS()
class DRR_API ADRREffectUnitBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADRREffectUnitBase();

	class UDA_EffectData* GetEffectData() { return EffectData; }
	void SetUser(AActor* user) { this->User = user; }
	void SetTarget(AActor* target) { this->Target = target; }
	void RemoveEffect();
	AActor* GetUser() { return User; }
	virtual void BeginFunc(AActor* target);
	virtual void UpdateFunc(AActor* target);
	virtual void EndFunc(AActor* target);
protected:


public:	


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EffectData)
	TObjectPtr<class UDA_EffectData> EffectData;

	TObjectPtr<AActor> User;

	TObjectPtr<AActor> Target;
	


};
