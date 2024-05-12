// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter/EnemyCharacterBase/NormalMonster.h"
#include "EnemyCharacter/EnemyCharacterBase/EnemyCharacterBase.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
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
	AMeleeMonsterBase(int Index);

	void CreateHitBoxBetweenBones(FName RightBoneName1, FName RightBoneName2, FName LeftBoneName1, FName LeftBoneName2);

	FRotator GetRotationForBone(FVector BoneX, FVector BoneY);

	virtual void MeleeAttack(FVector TargetLocation)override;

	virtual void MiddleAttack(FVector TargetLocation)override;

	virtual void LongAttack(FVector TargetLocation)override;

	//void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ComboAttack();

	void ComboAttackCount();

	void StartComboAttack();

	void ComboAttackProcess();

	virtual void SetCollision();

	void EndComboAttack(UAnimMontage* TargetMontage, bool bInterrupted);


	UFUNCTION() void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void StrongAttack();

	virtual void Guard();

	TObjectPtr<class UBoxComponent> RightWeaponHitBox;

	TObjectPtr<class UBoxComponent> LeftWeaponHitBox;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* ComboAttackHitBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	USphereComponent* MyOverlapSphere;

	float AttackSpeed=1;

	USkeletalMeshComponent* SkeletalMeshComp;
	USkeletalMeshComponent* SkeletalMeshComp2;
	FName BoneName1;
	FName BoneName2;

	FName BoneName3;
	FName BoneName4;

	FVector BonePosition1;
	FVector BonePosition2;
	FVector BonePosition3;
	FVector BonePosition4;

	FVector MidPoint;
	FVector Direction;


	FVector BoxExtent;

	bool IsComboAttacking = false;

	TArray<AActor*> HitedActor;

public:

	bool IsAttack = false;

	int32 ComboCount = 1;

	int32 MaxComboCount = 1;


};
