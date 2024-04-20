// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/ABWeaponItem.h"
#include "Item/ABItemDataTable.h"

// Sets default values
UABWeaponItem::UABWeaponItem()
{


	//Asset Path
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> Weapon_OneRef(TEXT("/Game/InfinityBladeWeapons/Weapon/Blade_Sucker/SK_Blade_Sucker.SK_Blade_Sucker"));
	//if (Weapon_OneRef.Succeeded())
	//{
	//	Weapon_One->SetSkeletalMesh(Weapon_OneRef.Object);
	//	Weapon_One->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));
	//	Weapon_One->SetCollisionProfileName(TEXT("NoCollision"));
	//}

	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> Weapon_TwoRef(TEXT("/Game/InfinityBladeWeapons/Weapon/Blade_Bubblewand/SK_Blade_Bubblewand.SK_Blade_Bubblewand"));
	//if (Weapon_TwoRef.Succeeded())
	//{
	//	Weapon_Two->SetSkeletalMesh(Weapon_TwoRef.Object);
	//	Weapon_Two->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));
	//	Weapon_Two->SetCollisionProfileName(TEXT("NoCollision"));
	//}

}

USkeletalMeshComponent* UABWeaponItem::GetWeapon()
{
	return nullptr;
}


