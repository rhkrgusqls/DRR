// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase/CharacterBase.h"
#include "PlayerCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API APlayerCharacterBase : public ACharacterBase
{
	GENERATED_BODY()
	
	APlayerCharacterBase();
	virtual void BeginPlay() override;
	void CreateSession();
	void FindSession();
	void Jump();

	void ReleaseQuaterMoveAction();

	void ReleaseShoulderMoveAction();
	
	void ReleaseShoulderLookAction();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)override;
protected:

	bool bQuaterMoveActionPressed = false;
	bool bShoulderMoveActionPressed = false;
	bool bShoulderLookActionPressed = false;

	TObjectPtr<class UInputMappingContext> Controller;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> QuaterMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShoulderMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShoulderLookAction;
};
