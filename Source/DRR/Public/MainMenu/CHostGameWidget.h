// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHostGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UCHostGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    void HostBtnClicked();

    UFUNCTION(BlueprintCallable)
    void BackBtnClicked();

protected:

    virtual void NativeOnInitialized() override;
    class ACMainMenuController* GetMenuController();
public:

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UEditableTextBox> SessionNameTextBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr < class USpinBox> MaxPlayersSpinBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr < class UButton> HostBtn;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr < class UButton> BackBtn;
};
