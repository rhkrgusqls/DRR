// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter/EnemyCharacterBase/NormalMonsterBase/MeleeMonsterBase.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "WarriorGoblin.generated.h"

UCLASS()
class DRR_API AWarriorGoblin : public AMeleeMonsterBase 
{
	GENERATED_BODY()
public:
	//FORCEINLINE class UBoxComponent* GetTrigger() { return LeftWeaponHitBox; }
	//FORCEINLINE class UBoxComponent* GetTrigger() { return RightWeaponHitBox; }

	AWarriorGoblin();
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetCollision()override;




};
