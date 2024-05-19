// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DRRMultiplayerManager.generated.h"

/**
 * 
 */



UCLASS()
class DRR_API UDRRMultiplayerManager : public UObject
{
	GENERATED_BODY()
	
public:

	UDRRMultiplayerManager();

	~UDRRMultiplayerManager();

	void SetMultiSubsystem(class UCMultiplaySubsystem* Subsystem) { MultiSubsystem = Subsystem; }

	UFUNCTION(Exec)
	void HostSession(FString RoomName);

	UFUNCTION(Exec)
	void Join_Address();
	UFUNCTION(Exec)
	void FindSession();


	UFUNCTION(Exec)
	void JoinSession(uint32 RoomNum);


	UFUNCTION(Exec)
	void LeaveSession();

protected:
	void FindFinish(const class TArray<FOnlineSessionSearchResult>& SessionResults, bool bwasSuccessful);

	class UCMultiplaySubsystem* MultiSubsystem;

};
