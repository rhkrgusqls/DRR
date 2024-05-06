// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ABItem.h"
#include "GameManager/ABGameInstance.h"

// Sets default values
AABItem::AABItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AABItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

