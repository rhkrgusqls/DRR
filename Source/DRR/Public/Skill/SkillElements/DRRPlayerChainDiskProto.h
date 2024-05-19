// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DRRPlayerChainDiskProto.generated.h"


UENUM()
enum class EDiskState : uint8
{
	Init,
	FindTarget,
	NoTarget,
	Max
};


UCLASS()
class DRR_API ADRRPlayerChainDiskProto : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADRRPlayerChainDiskProto();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Init(AActor* user, float damage);
	void NoTargetDead(float delta);
	bool CheckArrive();
	void CheckExpire();
	void Guide();
	bool FindTarget();
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	TObjectPtr<class UStaticMesh> Mesh;


	UPROPERTY(VisibleAnywhere, Category = Trigger)
	TObjectPtr<class USphereComponent> Trigger;


	TObjectPtr<class ACharacterBase> User;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TargetCheck)
	TObjectPtr<class AActor> Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DiskSetting)
	uint8 MaxTargetCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DiskSetting)
	float DetectRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DiskSetting)
	float ArriveThreshold=5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DiskSetting)
	float DeadTime = 3.0f;

	uint8 CurTargetCount;

	TArray<AActor*> Targeted;

	EDiskState DiskState;

	float Damage;


	float curDeadTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> DiskMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;


};
