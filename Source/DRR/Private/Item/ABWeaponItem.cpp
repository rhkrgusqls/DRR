// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/ABWeaponItem.h"

// Sets default values
AABWeaponItem::AABWeaponItem()
{
	Weapon1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon1;
	

	//Asset Path
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Weapon_One(TEXT("/Game/InfinityBladeWeapons/Weapon/Blade_Sucker/SK_Blade_Sucker.SK_Blade_Sucker"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Weapon_Two(TEXT("/Game/InfinityBladeWeapons/Weapon/Blade_Bubblewand/SK_Blade_Bubblewand.SK_Blade_Bubblewand"));

	if (Weapon_One.Succeeded())
	{
		Weapon1->SetSkeletalMesh(Weapon_One.Object);
	}

	if (Weapon_Two.Succeeded())
	{
		Weapon2->SetSkeletalMesh(Weapon_Two.Object);
	}
	
	Weapon1->SetCollisionProfileName(TEXT("NoCollision"));
}

void AABWeaponItem::Change()
{

}


