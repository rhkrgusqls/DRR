// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager/ABGameInstance.h"

#include "DataAsset/Item/DA_ItemData.h"



UABGameInstance::UABGameInstance()
{
	FString ItemDataPath = TEXT("/Game/AdvancedInventory/Item_Table.Item_Table");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABITEM(*ItemDataPath);
	if (DT_ABITEM.Succeeded())
	{
		ABItemTable = DT_ABITEM.Object;
	}
}

FData_Item* UABGameInstance::GetABItemData(int32 ID)
{
	return ABItemTable->FindRow<FData_Item>(*FString::FromInt(ID), TEXT(""));
}