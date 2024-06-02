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
	void Init(AActor* user, float damage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void NoTargetDead(float delta);
	bool CheckArrive();
	void CheckExpire();
	void Guide();
	bool FindTarget();
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnStaticMeshHit(class UPrimitiveComponent* HitComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	void MeshRotateEffect(float delta);
	
	void TargetAttackEffect();
	void CollideWallEffect();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	TObjectPtr<class UStaticMesh> Mesh;


	UPROPERTY(VisibleAnywhere, Category = Trigger)
	TObjectPtr<class USphereComponent> Trigger;


	TObjectPtr<class ACharacterBase> User;

	TObjectPtr<class AActor> Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DiskSetting)
	uint8 MaxTargetCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DiskSetting)
	float DetectRadius;

	uint8 CurTargetCount;
	TArray<AActor*> Targeted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DiskSetting)
	float ArriveThreshold=200.0f;

	EDiskState DiskState;

	float Damage;

	float DeadTime = 3.0f;
	float curDeadTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> DiskMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> EffectMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EffectSetting)
	FRotator EffectRotateSpeed;

};
