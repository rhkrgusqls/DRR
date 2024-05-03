// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Effect/DRREffectUnitBase.h"
#include "DRRPassiveActComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRR_API UDRRPassiveActComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDRRPassiveActComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AutoUpdate(float DeltaTime);
	void AutoUse();
	void AttackUse();
	void DamagedUse(TArray<AActor*> Victims);
	void HittedUse(AActor* Attacker);
	UFUNCTION(BlueprintCallable)
	void AddEffect(TSubclassOf<class ADRREffectUnitBase> Effect,AActor* User);
	bool RemoveEffect(TSubclassOf<class ADRREffectUnitBase> Effect);
	bool RemoveEffect(TSubclassOf<class ADRREffectUnitBase> Effect, AActor* User);
private:
	bool CheckDuplicate(TSubclassOf<class ADRREffectUnitBase> Effect, AActor* User);

	void CreateAuto(class ADRREffectUnitBase* Effect);
	void CreateHit(class ADRREffectUnitBase* Effect);
	void CreateDamage(class ADRREffectUnitBase* Effect);
	void CreateAttack(class ADRREffectUnitBase* Effect);


protected:
	TArray<class DRROnAutoEffect*>   AutoEffects;
	TArray<class DRROnHitEffect*>    HittedEffects;
	TArray<class DRROnDamageEffect*> DamagedEffects;
	TArray<class DRROnAttackEffect*> AttackEffects;

		
};
