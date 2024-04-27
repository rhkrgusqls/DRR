// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter/EnemyCharacterBase/NormalMonsterBase/MeleeMonsterBase.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/BoxComponent.h"
#include "WarriorGoblin.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API AWarriorGoblin : public AMeleeMonsterBase
{
	GENERATED_BODY()
public:
	AWarriorGoblin();

	void CreateHitBoxBetweenBones();
	virtual void BeginPlay() override;
	
	USkeletalMeshComponent* SkeletalMeshComp;

	FName BoneName1;
	FName BoneName2;

	FVector BonePosition1;
	FVector BonePosition2;


	FVector MidPoint;
	FVector Direction;


	FVector BoxExtent;

	UBoxComponent* HitBox;
};
