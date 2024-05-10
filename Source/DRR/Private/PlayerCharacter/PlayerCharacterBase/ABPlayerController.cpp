// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/PlayerCharacterBase/ABPlayerController.h"
#include "PlayerCharacter/PlayerCharacterBase/Multiplayer/DRRMultiplayerManager.h"

#include "UI/DRRUserWidget.h"
#include "GameManager/DRRMainGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"
#include "PlayerCharacter/PlayerCharacterBase/PlayerCharacterBase.h"
#include "Utilities/Multiplay/CMultiplaySubsystem.h"
#include "Online.h"

#include "Utilities/UtilityList.h"

AABPlayerController::AABPlayerController()
{
}

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

    MultiPlayManager = NewObject<UDRRMultiplayerManager>();
    MultiPlayManager->SetMultiSubsystem(GetGameInstance()->GetSubsystem<UCMultiplaySubsystem>());
    
    
    ADRRMainGameMode* GM = Cast<ADRRMainGameMode>(GetWorld()->GetAuthGameMode());

    if (GetGameInstance()->GetFirstLocalPlayerController() == this)
    {
        if (GM)
        {
            GM->SetHUDWidgets(this);

        }

    }


    

}

void AABPlayerController::RespawnPlayer()
{
    ADRRMainGameMode* GM = Cast<ADRRMainGameMode>(GetWorld()->GetAuthGameMode());

    if (GM)
    {
        // Find PlayerStart actor in the level
        APlayerStart* PlayerStart = nullptr;
        for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
        {
            PlayerStart = *It;
            break; 
        }

        if (PlayerStart)
        {

            FVector SpawnLoc = PlayerStart->GetActorLocation();

            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            APlayerCharacterBase* SpawnedCharacter = GetWorld()->SpawnActor<APlayerCharacterBase>(GM->DefaultPawnClass, SpawnLoc, FRotator::ZeroRotator, SpawnParams);
            Possess(SpawnedCharacter);
        }
        else
        {
            CLog::Log("PlayerStartPoint Not Found");
        }
    }

}

void AABPlayerController::KillPlayer()
{
    // Get reference to the controlled character
    APlayerCharacterBase* MyCharacter = Cast<APlayerCharacterBase>(GetPawn());
    if (MyCharacter)
    {
        
        MyCharacter->ReciveAttack(MyCharacter->MaxHP * 3.0f);
    }
}
void AABPlayerController::HostSession(FString RoomName)
{
    MultiPlayManager->HostSession(RoomName);
}

void AABPlayerController::FindSession()
{

    MultiPlayManager->FindSession();

}

void AABPlayerController::JoinSession(uint32 RoomNum)
{

    MultiPlayManager->JoinSession(RoomNum);

}

