// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ABPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API AABPlayerController : public APlayerController
{
	GENERATED_BODY()

	AABPlayerController();
	
public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	//TSubclassOf<class > HUDWidgetClass;

	//UPROPERTY()
	//class UDRRUserWidget* HUDWidget;
	
	virtual void BeginPlay() override;

	void RespawnPlayer();
	UFUNCTION(Exec)
	void KillPlayer();

	TArray<TObjectPtr<APawn>> GetAnotherPlayerPawn();
	UFUNCTION(Exec)
	void HostSession(FString RoomName);

	UFUNCTION(Exec)
	void FindSession();


	UFUNCTION(Exec)
	void JoinSession(uint32 RoomNum);



protected:
		

protected:
	UPROPERTY()
	TObjectPtr<class UDRRMultiplayerManager> MultiPlayManager;

};
