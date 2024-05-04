// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/DRRActUnitBase.h"
#include "DRRPlayerActUnitProto2.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ADRRPlayerActUnitProto2 : public ADRRActUnitBase
{
	GENERATED_BODY()
public:
	ADRRPlayerActUnitProto2();

	virtual TArray<FOnActFuncDelegate> GetActFunc() override;



protected:
	virtual void BeginFunc(AActor* User) override;
	virtual void EndFunc(AActor* User) override;

private:
	void Func1(AActor* User);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	TSubclassOf<class ADRRPlayerProjectileProto> Projectile;

};
