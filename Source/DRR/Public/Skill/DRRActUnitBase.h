// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/DRRActableInterface.h"
#include "DRRActUnitBase.generated.h"

UCLASS()
class DRR_API ADRRActUnitBase : public AActor, public IDRRActableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADRRActUnitBase();

	virtual TArray<FOnActFuncDelegate> GetActFunc() override;
	virtual class UDA_ActData* GetActData() override;

	virtual void BeginFunc(AActor* User) override;
	virtual void EndFunc(AActor* User) override;

	virtual IDRRActableInterface* IsAchieveCondition(float Threshold) override;

	void ActDestroy();

	void Expire();
protected:
	virtual void BeginPlay() override;

	IDRRActableInterface* CheckNextAct(uint8 num);

public:	


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActData)
	TObjectPtr<class UDA_ActData> ActData;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NextActData)
	TArray<TSubclassOf<class ADRRActUnitBase>> NextActClass;

	TArray<TObjectPtr<class ADRRActUnitBase>> NextActUnit;
	
	FTimerHandle ExpireHandle;

};
