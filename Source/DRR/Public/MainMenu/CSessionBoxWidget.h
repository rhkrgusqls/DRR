// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSessionBoxWidget.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UCSessionBoxWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	void Init(int32 index, int32 CurrentPlayers, int32 MaxPlayers, const FString& roomName);


	virtual void NativeOnInitialized() override;

	void OnJoinBtnClicked();

protected:



	uint32 Index;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> RoomIndexTxt;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> RoomNameTxt;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> RoomHeadCountTxt;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> JoinBtn;
};
