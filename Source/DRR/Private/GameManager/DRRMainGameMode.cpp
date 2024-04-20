// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/DRRMainGameMode.h"
#include "Engine/DataTable.h"
#include "Item/ABItemDataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

ADRRMainGameMode::ADRRMainGameMode()
{
	// Default Pawn
	static ConstructorHelpers::FClassFinder<APawn> PlayerCharRef(TEXT("/Script/DRR.PlayerCharacterBase"));
	if (PlayerCharRef.Class)
	{
		DefaultPawnClass = PlayerCharRef.Class;
	}

	// Player Controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerRef(TEXT("/Script/DRR.ABPlayerController"));
	if (PlayerControllerRef.Class)
	{
		PlayerControllerClass = PlayerControllerRef.Class;
	}

	// MainWidget
	static ConstructorHelpers::FClassFinder<UUserWidget> MainHUDWidgetRef(TEXT("/Game/Asset/UI/Main/WBP_MainHUD.WBP_MainHUD_C"));
	if (MainHUDWidgetRef.Class)
	{
		MainHUDWidgetClass = MainHUDWidgetRef.Class;
	}

	// ItemDataTable
	static ConstructorHelpers::FObjectFinder <UDataTable> ItemDataRef(TEXT("/Game/Blueprints/Item/ItemData.ItemData"));
	if (ItemDataRef.Object)
	{
		ItemDataTable = ItemDataRef.Object;
	}
}

void ADRRMainGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(MainHUDWidgetClass))
	{
		MainHUDWidget = Cast<UUserWidget>(CreateWidget(GetWorld(), MainHUDWidgetClass));

		if (IsValid(MainHUDWidget))
		{
			MainHUDWidget->AddToViewport();
		}
	}

	if (ItemDataTable != nullptr)
	{
		FItem* ItemTableRow = ItemDataTable->FindRow<FItem>(FName("20"), FString());
		//데이터 정보 정상적으로 들어오는거 확인 완료
		//UE_LOG(LogDataTable, Log, TEXT("Name: {}"), ItemTableRow);
	}
}
