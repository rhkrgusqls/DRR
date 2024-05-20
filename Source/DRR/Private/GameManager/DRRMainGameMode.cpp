// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/DRRMainGameMode.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Utilities/UtilityList.h"
#include "GameManager/DRRPlayerState.h"
#include "GameManager/DRRGameState.h"
#include "PlayerCharacter/PlayerCharacterBase/ABPlayerController.h"
#include "TimerManager.h"

ADRRMainGameMode::ADRRMainGameMode()
{
	// Default Pawn
	static ConstructorHelpers::FClassFinder<APawn> PlayerCharRef(TEXT("/Game/Blueprints/Player/Test/BP_PlayerCharacterBase.BP_PlayerCharacterBase_C"));
	if (PlayerCharRef.Class)
	{
		DefaultPawnClass = PlayerCharRef.Class;
	}

	

	// Loding Screen
	static ConstructorHelpers::FClassFinder<UUserWidget> LodingScreenRef(TEXT("/Game/Asset/UI/Main/WBP_LodingScreen.WBP_LodingScreen_C"));
	if (LodingScreenRef.Class)
	{
		LodingScreenWidgetClass = LodingScreenRef.Class;
	}

	//LodingScreen = CreateDefaultSubobject<UWidgetComponent>(TEXT("LodingScreen"));
	
	PlayerControllerClass =  AABPlayerController::StaticClass();
	
	PlayerStateClass=ADRRPlayerState::StaticClass();
	//
	GameStateClass = ADRRGameState::StaticClass();
}



void ADRRMainGameMode::BeginPlay()
{
	Super::BeginPlay();
	//SetHUDWidgets(GetGameInstance()->GetFirstLocalPlayerController());

	//if (ItemDataTable != nullptr)
	//{
	//	FItem* ItemTableRow = ItemDataTable->FindRow<FItem>(FName("20"), FString());
	//	//데이터 정보 정상적으로 들어오는거 확인 완료
	//	//UE_LOG(LogDataTable, Log, TEXT("Name: {}"), ItemTableRow);
	//}
	float TimeToShowLoding = 0.2f;
	GetWorldTimerManager().SetTimer(ShowLodingTimer, this, &ADRRMainGameMode::ShowLodingScreen, TimeToShowLoding, false);
	

	float TimeToDelegate = 5.0f;
	
	GetWorldTimerManager().SetTimer(LodingTimer, this, &ADRRMainGameMode::DeleteLodingScreen,
		 TimeToDelegate, false);

}

void ADRRMainGameMode::PostLogin(APlayerController* newPlayer)
{
	Super::PostLogin(newPlayer);
	CDisplayLog::Log(TEXT("NewLogin"));
	CDisplayLog::Log(TEXT("%s"), *(MatchState.ToString()));
	// Ensure the new player has a pawn
	if (newPlayer && newPlayer->GetPawn() == nullptr)
	{
		CDisplayLog::Log(TEXT("NoPawn"));
		APawn* NewPawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass);
		if (NewPawn)
		{
			newPlayer->Possess(NewPawn);
		}
	}

	
	
}
void ADRRMainGameMode::ShowLodingScreen()
{
	if (IsValid(LodingScreenWidgetClass))
	{
		LodingScreenWidget = Cast<UUserWidget>(CreateWidget(GetWorld(), LodingScreenWidgetClass));
		if (IsValid(LodingScreenWidget))
		{
			LodingScreenWidget->AddToViewport();
		}
	}
}

void ADRRMainGameMode::DeleteLodingScreen()
{
	if (LodingScreenWidget)
	{
		LodingScreenWidget->RemoveFromParent();
	}
}

void ADRRMainGameMode::CMDGameStart()
{
	StartMatch();
}
