// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/DRRActUnitBase.h"
#include "DRRPlayerActUnitProto8.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ADRRPlayerActUnitProto8 : public ADRRActUnitBase
{
	GENERATED_BODY()

public:
	ADRRPlayerActUnitProto8();

	virtual TArray<FOnActFuncDelegate> GetActFunc() override;



protected:
	virtual void BeginFunc(AActor* User) override;
	virtual void EndFunc(AActor* User) override;

private:
	void Func1(AActor* User);
	FVector SetLocate(AActor* User,FVector loc);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WallSetting)
	TSubclassOf<class ADRRPlayerStoneWallProto> StoneWall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WallSetting)
	FVector Loc;

};
