// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DRRPlayerMagicArrowProto.generated.h"

UENUM()
enum class EArrowState : uint8
{
	Init,
	Eject,
	Stuck,
	Max
};



UCLASS()
class DRR_API ADRRPlayerMagicArrowProto : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADRRPlayerMagicArrowProto();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Init(AActor* user, float damage);
	void SetDelay(float delay);// {  }
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void SetTimer();
	
protected:
	void Eject();
	void Explosion();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	TObjectPtr<class UStaticMesh> Mesh;


	UPROPERTY(VisibleAnywhere, Category = Trigger)
	TObjectPtr<class USphereComponent> Trigger;


	TObjectPtr<class ACharacterBase> User;

	float Damage;

	float FireDelay;

	EArrowState ArrowState;


	float ArrowInitialSpeed = 3000.0f;
	float ArrowMaxSpeed = 3000.0f;
	FVector ArrowVelocity;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> MissileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;

	FTimerHandle TimeHandler;

};
