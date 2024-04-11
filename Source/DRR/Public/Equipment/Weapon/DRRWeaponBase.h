// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/DRRActableInterface.h"
#include "DRRWeaponBase.generated.h"

UCLASS()
class DRR_API ADRRWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADRRWeaponBase();

	virtual class IDRRActableInterface* GetFirstAct() ;
	virtual class IDRRActableInterface* GetSecondAct() ;

	class UDA_WeaponData* GetWeaponData() { return WeaponData; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	


protected:

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = WeaponData)
	TObjectPtr<class UDA_WeaponData> WeaponData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActData)
	TSubclassOf<class UDRRActUnitBase> FirstAct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActData)
	TSubclassOf<class UDRRActUnitBase> SecondAct;




};
