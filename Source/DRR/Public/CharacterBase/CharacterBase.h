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
class DRR_API ACharacterBase : public ACharacter, public IDRRCharacterWidgetInterface, public IDRRActorInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

public:
	virtual void BeginPlay() override;
	virtual void SetupCharacterWidget(class UDRRUserWidget* InUserWidget) override;

	virtual void ActFunc() override;

	class UDRRActComponent* GetActComponent() const { return ActComponent; }

protected:
	virtual void SetCharacterControlData(const class UPlayerControlDataAsset* CharacterControlData);

	void SetMaxHP(float NewHP);
	void SetHP(float NewHP);

protected:
	TMap< ECharacterControlType, class UPlayerControlDataAsset*> CharacterControlManager; // 생성자가 호출될떄 같이 메모리 할당

	
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Act, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UDRRActComponent> ActComponent;
public:		
	virtual void Tick(float DeltaTime) override;

	float ApplyDamage(float InDamage);

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta= ( AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> PlayerHUD;

	FOnHPZeroDelegate OnHPZero;
	FOnHPChangedDelegate OnHPChanged;

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

};
