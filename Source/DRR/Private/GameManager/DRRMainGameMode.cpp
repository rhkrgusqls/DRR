// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager/DRRMainGameMode.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Utilities/UtilityList.h"

ADRRMainGameMode::ADRRMainGameMode()
{
	// Default Pawn
	static ConstructorHelpers::FClassFinder<APawn> PlayerCharRef(TEXT("/Game/Blueprints/Player/Test/BP_PlayerCharacterBase.BP_PlayerCharacterBase_C"));
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

	//ItemListWidget
	static ConstructorHelpers::FClassFinder<UUserWidget> ItemListUIRef(TEXT("/Game/Asset/UI/Main/WBP_ItemList.WBP_ItemList_C"));
	if (ItemListUIRef.Class)
	{
		ItemListWidgetClass = ItemListUIRef.Class;
	}

	//ItemCardWidget (used inside of ItemListWidget)
	static ConstructorHelpers::FClassFinder<UUserWidget> ItemCardRef(TEXT("/Game/Asset/UI/Main/WBP_ItemListCard.WBP_ItemListCard_C"));
	if (ItemCardRef.Class)
	{
		ItemCardWidgetClass = ItemCardRef.Class;
	}

	// Interact Alert
	static ConstructorHelpers::FClassFinder<UUserWidget> InteractAlertRef(TEXT("/Game/Asset/UI/Main/WBP_InteractAlert.WBP_InteractAlert_C"));
	if (InteractAlertRef.Class)
	{
		InteractAlertClass = InteractAlertRef.Class;
	}

}

void ADRRMainGameMode::BeginPlay()
{
	Super::BeginPlay();
	//SetHUDWidgets(GetGameInstance()->GetFirstLocalPlayerController());

	if (ItemDataTable != nullptr)
	{
		FItem* ItemTableRow = ItemDataTable->FindRow<FItem>(FName("20"), FString());
		//데이터 정보 정상적으로 들어오는거 확인 완료
		//UE_LOG(LogDataTable, Log, TEXT("Name: {}"), ItemTableRow);
	}
}

void ADRRMainGameMode::PostLogin(APlayerController* newPlayer)
{
	Super::PostLogin(newPlayer);
	
}

void ADRRMainGameMode::SetHUDWidgets(APlayerController* Player)
{
	CDisplayLog::Log(TEXT("Try SetHUDWidgets"));
	//MainHUD
	if (IsValid(MainHUDWidgetClass))
	{

		CDisplayLog::Log(TEXT("IsValid Widget"));
		MainHUDWidget = Cast<UUserWidget>(CreateWidget(Player->GetWorld(), MainHUDWidgetClass));

		if (IsValid(MainHUDWidget))
		{
			MainHUDWidget->AddToViewport();
		}
	}

	//ItemList (It will be moved to other function() when GetItem() function or else is ready)
	if (IsValid(ItemListWidgetClass))
	{
		ItemListWidget = Cast<UUserWidget>(CreateWidget(Player->GetWorld(), ItemListWidgetClass));

		if (IsValid(ItemListWidget))
		{
			// add the function of Adding this UI after the event of Item Collect

			//ItemListWidget->AddToViewport();

			// add the function of deleting this UI after 3 seconds
			//GetWorldTimerManager().SetTimer(TimerHandle, ItemListWidget, ItemListWidget->SetVisibility(ESlateVisibility::Hidden), 3.0f, false);
			// Seems it need Other Function() to use it
		}
	}

	//ItemCard (It will be moved to other function() when GetItem() function or else is ready)
	if (IsValid(ItemCardWidgetClass))
	{
		ItemCardWidget = Cast<UUserWidget>(CreateWidget(Player->GetWorld(), ItemCardWidgetClass));

		if (IsValid(ItemCardWidget))
		{
			// contents about (1) Getting the name of collected Item / (2) Getting the amount of collected Item
		}
	}

	// Interact Alert (It will be moved to other function() soon)
	if (IsValid(InteractAlertClass))
	{
		InteractAlert = Cast<UUserWidget>(CreateWidget(Player->GetWorld(), InteractAlertClass));

		if (IsValid(InteractAlert))
		{
			// contents about (1) Getting the event of Interactive Item on sight / (2) Getting the event of Interactive Item out of sight
			// (1) InteractAlert-> SetVisibility(ESlateVisibility::Visible) / (2) InteractAlert-> SetVisibility(ESlateVisibility::Hidden)
		}
	}


}
