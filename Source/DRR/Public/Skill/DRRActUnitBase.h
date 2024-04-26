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
	virtual FOnActFuncDelegate GetBeginActFunc() override;
	virtual FOnActFuncDelegate GetEndActFunc() override;
	virtual class UDA_ActData* GetActData() override;

	virtual FOnActCheckConditionDelegate GetAchieveCondition() override;

protected:
	virtual void BeginFunc(AActor* User);
	virtual void EndFunc(AActor* User);

	UFUNCTION()
	virtual bool IsAchieveCondition(AActor* User);

public:	


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActData)
	TObjectPtr<class UDA_ActData> ActData;



};
