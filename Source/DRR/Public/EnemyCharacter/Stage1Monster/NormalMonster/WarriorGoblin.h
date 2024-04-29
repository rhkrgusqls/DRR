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
	virtual void Tick(float DeltaTime) override;
	FRotator GetRotationForBone(FVector BoneX, FVector BoneY);

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

};
