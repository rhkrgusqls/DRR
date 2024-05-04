// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "EnemyCharacter/EnemyCharacterBase/EnemyCharacterBase.h"
#include "NormalMonster.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ANormalMonster : public AEnemyCharacterBase
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UWidgetComponent> HPBarUI;
	TObjectPtr<class UProgressBar> HPPrgressBar;

	ANormalMonster();
	ANormalMonster(int Type);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void ReciveAttack(float physicsDamage/*, float MagicDamage*/) override;
	void SetHPBarHiddenTimer();
	void HideHPBar();

private:
	FTimerHandle HPBarHideTimerHandle;
};
