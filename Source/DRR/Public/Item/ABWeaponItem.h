// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABWeaponItem.generated.h"

UCLASS()
class DRR_API UABWeaponItem : public UABItemDataTable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UABWeaponItem();

protected:

public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	TSoftObjectPtr<USkeletalMesh> WeaponMesh;

	USkeletalMeshComponent* GetWeapon();

};