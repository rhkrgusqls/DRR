// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DBNormalEnemyAnimMongtage.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FEnemyAnimSet
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> NormalAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage>EnforceAttackMontage;

	//ChargingAttack By occupation Usage
	//NormalEnemy:Guarding
	//MagicEnemy:CastAttack
	//HealerEnemy:Healing
	//CommenderEnemy:Unit rally
	//-kwakhyunbin
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ChargingAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> KnockbackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> StiffnessMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> DeadMontage;
};

UCLASS()
class UDBNormalEnemyAnimMongtage : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimData")
	TArray<FEnemyAnimSet> SEnemyAnim;
};
