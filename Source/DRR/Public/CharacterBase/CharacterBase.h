// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class DRR_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
protected:

	//Set Capsule Value-Kwakhyunbin
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Capsule")
	float CapsuleSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Capsule")
	float CapsuleHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Capsule")
	FString CapsuleProfileName;

	//Set Mesh Value-Kwakhyunbin
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	FVector MeshVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	FRotator MeshRotator;

	//Set Movement Value-Kwakhyunbin
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool CharacterbOrientRotationToMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	FRotator CharacterRotationRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float CharacterJumpZVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float CharacterAirControl;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float CharacterMaxWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float CharacterMinAnalogWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float CharacterBrakingDecelerationWalking;

	//Set Mesh and Anim BP-Kwakhyunbin
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<class USkeletalMesh> CharacterMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	TSubclassOf<class UAnimInstance> CharacterAnimBP;


};
