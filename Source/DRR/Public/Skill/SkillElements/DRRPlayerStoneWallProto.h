// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DRRPlayerStoneWallProto.generated.h"


UENUM()
enum class EWallState : uint8
{
	Init,
	Ambush,
	Rising,
	Stay,
	Expire,
	Max
};


UCLASS()
class DRR_API ADRRPlayerStoneWallProto : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADRRPlayerStoneWallProto();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetFloor();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Init(AActor* user, float damage);

protected:

	void SetRisingTimer();
	void SetExpireTimer();
	void Arise();
	void Rising(float delta);


	void Expire();
	void Expiring(float delta);
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DelayTime)
	float DelayTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DelayTime)
	float RisingTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DelayTime)
	float ExpireTime;

	float Damage;
	TObjectPtr<class AActor> User;

	EWallState WallState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMesh> Mesh;

	UPROPERTY(VisibleAnywhere, Category = Trigger)
	TObjectPtr<class UBoxComponent> Trigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> PillarMesh;

	TArray<class AActor*> Hitted;

	FString CollisionChannelName;
	struct FTimerHandle RiseupTimerHandle;

	FVector OriginPos;

};
