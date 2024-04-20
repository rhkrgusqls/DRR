// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "Interface/DRRActorInterface.h"
#include "Interface/DRRCharacterWidgetInterface.h"
#include "CharacterBase.generated.h"


UENUM()
enum class ECharacterControlType : uint8
{
	Quater
};

UCLASS()
class DRR_API ACharacterBase : public ACharacter, public IDRRActorInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

public:
	virtual void BeginPlay() override;
	

	virtual void ActFunc() override;

	class UDRRActComponent* GetActComponent() const { return ActComponent; }

protected:
	virtual void SetCharacterControlData(const class UPlayerControlDataAsset* CharacterControlData);

	

protected:
	TMap< ECharacterControlType, class UPlayerControlDataAsset*> CharacterControlManager; // 생성자가 호출될떄 같이 메모리 할당

	
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Act, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UDRRActComponent> ActComponent;
public:		
	virtual void Tick(float DeltaTime) override;

	void ReciveAttack(float physicsDamage/*, float MagicDamage*/);

	void SetDotDamage(float TickDamage, float DurationTime);

	void RemoveDotDamage(float TickDamage);

	virtual void IsDead();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float MaxHP;

	float DotDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float MaxMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float CurrentMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float MaxST;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float CurrentST;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float physicsAttack;		

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float physicsDef=1;

	//Not Use
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	//float MagicAttack;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	//float MagicDef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float HPRegenSpeed;

	float HPRegenHandle;


//AnimMongtage-kwakhyunbin

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> NormalAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage>EnforceAttackMontage;

	//ChargingAttack By occupation Usage
	//NormalEnemy:Guarding
	//MagicEnemy:CastAttack
	//HealerEnemy:Healing
	//CommenderEnemy:Unit rally
	//-kwakhyunbin
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ChargingAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> KnockbackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> StiffnessMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> DeadMontage;


	FOnHPChangedDelegate OnHPChanged;
};
