// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DRRPlayerStonePillarProto.generated.h"

UCLASS()
class DRR_API ADRRPlayerStonePillarProto : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADRRPlayerStonePillarProto();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetFloor();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Init(AActor* user, float damage);
	void SetTimer();
	void Arise();
	void Expire();
	UFUNCTION()
	void OnPillarHit(AActor* SelfActor, AActor* OtherActor);
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DelayTime)
	float DelayTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DelayTime)
	float ExpireTime;

	float Damage;
	TObjectPtr<class AActor> User;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMesh> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> PillarMesh;

	TArray<class AActor*> Hitted;

	FString CollisionChannelName;
	struct FTimerHandle RiseupTimerHandle;
	

};
