// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter/EnemyCharacterBase/NormalMonster.h"
#include "ArrowGoblin.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API AArrowGoblin : public ANormalMonster
{
	GENERATED_BODY()
public:
	//FORCEINLINE class UBoxComponent* GetTrigger() { return LeftWeaponHitBox; }
	//FORCEINLINE class UBoxComponent* GetTrigger() { return RightWeaponHitBox; }

	AArrowGoblin();

	virtual void BeginPlay() override;

	virtual void MeleeAttack(FVector TargetLocation)override;

	virtual void MiddleAttack(FVector TargetLocation)override;

	virtual void LongAttack(FVector TargetLocation)override;

	void IncreaseDistance(FVector TargetLocation);

	void FireArrow(FVector TargetLocation);

	void KickAndRun(FVector TargetLocation);

	TArray <TObjectPtr<class AArrowBullet>> Arrow;
	bool IsRun;
	int32 ArrowNum=0;
};
