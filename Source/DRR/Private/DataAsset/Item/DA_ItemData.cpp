// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/Item/DA_ItemData.h"

FPrimaryAssetId UDA_ItemData::GetPrimaryAssetId() const
{
    return FPrimaryAssetId("DA_ItemData", GetFName());
}
