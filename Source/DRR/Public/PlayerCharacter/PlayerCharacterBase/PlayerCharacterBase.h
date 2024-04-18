// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "CharacterBase/CharacterBase.h"
#include "Animation/PlayerAnim/DRRAnimInstance.h"
#include "PlayerCharacterBase.generated.h"

UCLASS()
class DRR_API APlayerCharacterBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	APlayerCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void SetCharacterControlData(const class UPlayerControlDataAsset* CharacterControlData) override;

	virtual void EquipWeapon(class UABItemDataTable* InItemData);
	//virtual void DrinkPotion(class UABItemDataTable* InItemData);
	//virtual void ReadScroll(class UABItemDataTable* InItemData);

private:
	void QuaterMove(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
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
	bool IsSit = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> weaponChangeAction;

	// Item
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	//TArray<UABItemData> Inventory;

	// ChangeWeapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	TObjectPtr<class UABWeaponItem> Weapon1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	TObjectPtr<class UABWeaponItem> Weapon2;

	
	TObjectPtr<class USkeletalMeshComponent> CurWeapon;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	TArray<TObjectPtr<class UABWeaponItem>> WeaponList =  { Weapon1, Weapon2 };
	
	FName WeaponSocket = "Tumb2_R";

	

private:
	//ECharacterControlType CurrentCharacterControlType;

};
