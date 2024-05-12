// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "CharacterBase/CharacterBase.h"
#include "Animation/PlayerAnim/DRRAnimInstance.h"

#include "Interface/DRRActableInterface.h"
#include "Interface/DRRCharacterWidgetInterface.h"
#include "Components/ProgressBar.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#include "PlayerCharacterBase.generated.h"

UCLASS()
class DRR_API APlayerCharacterBase : public ACharacterBase, public IDRRCharacterWidgetInterface
{
	GENERATED_BODY()

public:
	APlayerCharacterBase();

	virtual void SetupCharacterWidget(class UDRRUserWidget* InUserWidget) override;

	virtual void IsDead() override;
	virtual void PossessedBy(AController* NewController) override;

	void SetHUDWidgets(APlayerController* Player);

	FORCEINLINE UUserWidget* GetMainHUDWidget() { return MainHUDWidget; }
	FORCEINLINE UUserWidget* GetItemListWidget() { return ItemListWidget; }
	FORCEINLINE UUserWidget* GetItemCardWidget() { return ItemCardWidget; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float Deltatime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void SetCharacterControlData(const class UPlayerControlDataAsset* CharacterControlData) override;

	virtual void GetLifetimeReplicatedProps(TArray < FLifetimeProperty>& OutLifetimeProps) const override;

	void SetMaxHP(float NewHP);

	UFUNCTION(BlueprintCallable)
	void SetHP(float NewHP);

	void SetMaxMP(float NewMP);
	void SetMP(float NewMP);

	void SetMaxST(float NewST);
	void SetST(float NewST);

	void SetMaxGold(int NewGold);
	void SetGold(int NewGold);

private:
	void QuaterMove(const FInputActionValue& Value);
	
	void WeaponLeftAttackPress(const FInputActionValue& Value);
	void WeaponRightAttackPress(const FInputActionValue& Value);
	void WeaponLeftAttackRelaease(const FInputActionValue& Value);
	void WeaponRightAttackRelaease(const FInputActionValue& Value);
	
	void WeaponLeftAct();
	void WeaponLeftActRelease();
	void WeaponRightAct();
	void WeaponRightActRelease();

	UFUNCTION(Server,Reliable,WithValidation,Category="RPC_Character")
	void ServerLeftAct();

	UFUNCTION(NetMulticast,Unreliable,Category="RPC_Character")
	void MulticastLeftAct();

	UFUNCTION(Server, Reliable, WithValidation, Category = "RPC_Character")
	void ServerLeftActRelease();

	UFUNCTION(NetMulticast, Unreliable, Category = "RPC_Character")
	void MulticastLeftActRelease();


	UFUNCTION(Server, Reliable, WithValidation, Category = "RPC_Character")
	void ServerRightAct();

	UFUNCTION(NetMulticast, Unreliable, Category = "RPC_Character")
	void MulticastRightAct();

	UFUNCTION(Server, Reliable, WithValidation, Category = "RPC_Character")
	void ServerRightActRelease();

	UFUNCTION(NetMulticast, Unreliable, Category = "RPC_Character")
	void MulticastRightActRelease();


	void Sit(const FInputActionValue& Value);
	
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
	TObjectPtr<class UInputAction> ItemUseAction;

	//Attack
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ActLeftPressAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ActRightPressAction;

	//TestWeapon
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Weapon, Meta = (AllowPrivateAccess = "true"));
	TSubclassOf<class ADRRWeaponBase> Weapon;
	TObjectPtr<class ADRRWeaponBase> WeaponRef;


	//UI
	TSubclassOf<UUserWidget> MainHUDWidgetClass;
	UUserWidget* MainHUDWidget;

	//Collected Item Alert List UI
	TSubclassOf<UUserWidget> ItemListWidgetClass;
	UUserWidget* ItemListWidget;

	//ItemCard content UI(Used inside of Collected Item Alert List UI)
	TSubclassOf<UUserWidget> ItemCardWidgetClass;
	UUserWidget* ItemCardWidget;


private:
	ECharacterControlType CurrentCharacterControlType;

	TObjectPtr<class UDRRUserWidget> HUDWidget;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> PlayerHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	int32 MaxGold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	int32 CurrentGold;


	FOnHPZeroDelegate OnHPZero;
	FOnHPChangedDelegate OnHPChanged;
	FOnMPChangedDelegate OnMPChanged;
	FOnSTChangedDelegate OnSTChanged;
	FOnGoldChangedDelegate OnGoldChanged;
	//FOnItemGetDelegate OnItemGet;
};
