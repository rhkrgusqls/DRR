// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter/EnemyCharacterBase/NormalMonster.h"
#include "EnemyCharacter/EnemyCharacterBase/EnemyCharacterBase.h"
#include "Components/SphereComponent.h"
#include "MeleeMonsterBase.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API AMeleeMonsterBase : public ANormalMonster
{
	GENERATED_BODY()
public:
	AMeleeMonsterBase();

	virtual void MeleeAttack(FVector TargetLocation)override;

	virtual void MiddleAttack(FVector TargetLocation)override;

	virtual void LongAttack(FVector TargetLocation)override;

	void ComboAttack();

	void StartComboAttack();
	void EndComboAttack();


	void OnAttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void StrongAttack();

	virtual void Guard();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* ComboAttackHitBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	USphereComponent* MyOverlapSphere;
};
