// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/WorldTravelPortal.h"

// Sets default values
AWorldTravelPortal::AWorldTravelPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AWorldTravelPortal::TravelWorldServer()
{
    if (HasAuthority())
    {
        ServerTravelWorld();
    }
    else
    {
        //ServerTravelWorld();
    }
}

void AWorldTravelPortal::ServerTravelWorld()
{
    if (GetWorld())
    {
        GetWorld()->ServerTravel("/Game/Levels/DebugTestLevel?listen");
    }
}

