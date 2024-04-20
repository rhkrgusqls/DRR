// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DRRUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UDRRUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetOwningActor(AActor* NewOwner) { OwningActor = NewOwner; }
	FORCEINLINE void SetMaxHP(float NewHP) { MaxHP = NewHP; }
	FORCEINLINE void SetMaxMP(float NewMP) { MaxMP = NewMP; }
	void UpdateHP(float NewHP);
	void UpdateMP(float NewMP);
	
protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Actor)
	TObjectPtr<AActor> OwningActor;

	//TObjectPtr<class UProgressBar> EnemyHPProgressBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = ( BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<class UProgressBar> PlayerHPBar;
	TObjectPtr<class UProgressBar> PlayerMPBar;
	float MaxHP;
	float MaxMP;
};
