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
	//ACharacterBase(int Type = 0);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	FORCEINLINE void SetMaxHP(float NewHP) { MaxHP = NewHP; }
	void UpdateHP( float NewHP );

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float physicsAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float MagicAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float physicsDef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float MagicDef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float HPRegenSpeed;

	float HPRegenHandle;

};
