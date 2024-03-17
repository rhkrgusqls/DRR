// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"


UENUM()
enum class ECharacterControlType : uint8
{
	Quater
};

UCLASS()
class DRR_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	virtual void SetCharacterControlData(const class UCharacterControlDataAsset* CharacterControlData);

protected:
	TMap< ECharacterControlType, class UCharacterControlDataAsset*> CharacterControlManager; // 생성자가 호출될떄 같이 메모리 할당

public:		
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float physicsAttack;		

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float physicsDef;

	//Not Use
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	//float MagicAttack;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	//float MagicDef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float HPRegenSpeed;

	float HPRegenHandle;

};
