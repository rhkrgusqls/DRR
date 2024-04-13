// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "CharacterBase/CharacterBase.h"
#include "Animation/PlayerAnim/DRRAnimInstance.h"
#include "Interface/DRRCharacterWidgetInterface.h"
#include "PlayerCharacterBase.generated.h"

UCLASS()
class DRR_API APlayerCharacterBase : public ACharacterBase, public IDRRCharacterWidgetInterface
{
	GENERATED_BODY()

public:
	APlayerCharacterBase();

	virtual void SetupCharacterWidget(class UDRRUserWidget* InUserWidget) override;
	float ApplyDamage(float InDamage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void SetCharacterControlData(const class UPlayerControlDataAsset* CharacterControlData) override;

	void SetMaxHP(float NewHP);
	void SetHP(float NewHP);

private:
	void QuaterMove(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);

	void WeaponLeftAttackPress(const FInputActionValue& Value);
	void WeaponRightAttackPress(const FInputActionValue& Value);
	void WeaponLeftAttackRelaease(const FInputActionValue& Value);
	void WeaponRightAttackRelaease(const FInputActionValue& Value);

	void Sit(const FInputActionValue& Value);
	void weaponChange(const FInputActionValue& Value);

	void SetCharacterControl(ECharacterControlType ControlType);

protected:
	//Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	//Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> QuaterMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> SitAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ActLeftPressAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ActRightPressAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> weaponChangeAction;

	//ChangeWeapon
	TArray<TObjectPtr<class UABWeaponItemData>> WeaponList;

	uint8 curWeapon = 0;

	bool IsSit = false;

	//TestWeapon
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Weapon, Meta = (AllowPrivateAccess = "true"));
	TSubclassOf<class ADRRWeaponBase> Weapon;


private:
	ECharacterControlType CurrentCharacterControlType;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> PlayerHUD;

	FOnHPZeroDelegate OnHPZero;
	FOnHPChangedDelegate OnHPChanged;

};
