// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArrowBullet.generated.h"

UCLASS()
class DRR_API AArrowBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArrowBullet();

protected:
	UFUNCTION() void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	void SetDamage(float ReciveDamage);

	void Fire();
	TObjectPtr<class UStaticMeshComponent> Arrow;
	TObjectPtr<class UBoxComponent> ArrowHitBox;
	float Damage=10;
};
