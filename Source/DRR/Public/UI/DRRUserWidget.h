// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
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
	FORCEINLINE void SetMaxST(float NewST) { MaxST = NewST; }
	FORCEINLINE UTextBlock* GetGoldAmount() { return CurrentGold; }
	UFUNCTION(BlueprintCallable)
	void UpdateHP(float NewHP);
	void UpdateMP(float NewMP);
	void UpdateST(float NewST);
	void UpdateGold(int32 NewGold);

protected:
	void FillAnimationMap();

public:
	UFUNCTION(BlueprintCallable)
	UWidgetAnimation* GetAnimationByName(const FName& AnimationName) const;

	UFUNCTION(BlueprintCallable)
	bool PlayAnimationByName(const FName& AnimationName, float StartAtTime = 0.0f, int32 NumLoopsToPlay = 1, EUMGSequencePlayMode::Type PlayMode = EUMGSequencePlayMode::Forward, float PlayBackSpeed = 1.0f);
	
protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Actor)
	TObjectPtr<AActor> OwningActor;

	//TObjectPtr<class UProgressBar> EnemyHPProgressBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = ( BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<class UProgressBar> PlayerHPBar;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<class UProgressBar> PlayerMPBar;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<class UProgressBar> PlayerSTBar;

	float MaxHP;
	float MaxMP;
	float MaxST;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<class UTextBlock> CurrentGold;
	FText GoldText;

	TMap<FName, UWidgetAnimation*> AnimationsMap;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<class UUserWidget> Inventory_UI;*/

};
