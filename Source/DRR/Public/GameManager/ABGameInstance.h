// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ABGameInstance.generated.h"

/**
 * 
 */

struct FData_Item;
class UDataTable;


UCLASS()
class DRR_API UABGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UABGameInstance();
	FData_Item* GetABItemData(int32 ID);

private:
	UPROPERTY()
	UDataTable* ABItemTable;
};
