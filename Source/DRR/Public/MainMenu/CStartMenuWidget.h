// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CStartMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UCStartMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnSinglePlayClicked();
	UFUNCTION()
	void OnHostClicked();
	UFUNCTION()
	void OnJoinClicked();
	UFUNCTION()
	void OnExitClicked();




protected:
	
	UPROPERTY(meta=(BindWidget))
	class UButton* SinglePlayBtn;
	UPROPERTY(meta = (BindWidget))
	class UButton* HostBtn;
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinBtn;
	UPROPERTY(meta = (BindWidget))
	class UButton* ExitBtn;

};
