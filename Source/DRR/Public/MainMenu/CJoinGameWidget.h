// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CJoinGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UCJoinGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    void FindButtonClicked();

    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    void JoinButtonClicked();

    UFUNCTION(BlueprintCallable)
    void BackBtnClicked();
protected:

    virtual void NativeOnInitialized() override;

    void FindFinish(const class TArray<FOnlineSessionSearchResult>& SessionResults, bool bwasSuccessful);
public:
    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    void OnSessionFound(const FString& SessionName, int32 CurrentPlayers, int32 MaxPlayers, int32 SessionIndex);


    UPROPERTY(meta = (BindWidget))
    TObjectPtr < class UButton> BackBtn;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> FindButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr <class UScrollBox> SessionListScrollBox;
};
