// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DRRGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UDRRGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UDRRGameInstance();

	virtual void Init() override;

	UFUNCTION(Exec)
	void Hello();
	

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join_Address();
	UFUNCTION(Exec)
	void Find();


	UFUNCTION(Exec)
	void Join(uint32 RoomNum);

protected:
	void FindFinish(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bwasSuccessful);

};
