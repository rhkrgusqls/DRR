// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/Bullet/ArrowBullet.h"
#include "CharacterBase/CharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
AArrowBullet::AArrowBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Arrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowRef(TEXT("/Script/Engine.StaticMesh'/Game/ProtoTypeAsset/DownLoadAsset/PolygonFantasyCharacters/Items/SM_Prop_Broom_01.SM_Prop_Broom_01'"));
	if (ArrowRef.Object)
	{
		Arrow->SetStaticMesh(ArrowRef.Object);
		Arrow->SetCollisionProfileName("NoCollision");
	}

	ArrowHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ArrowHitBox"));

	if (ArrowHitBox)
	{
		ArrowHitBox->SetBoxExtent(FVector(5.0f, 0.5f, 0.5f));
		ArrowHitBox->SetCollisionProfileName("NoCollision");
		ArrowHitBox->OnComponentBeginOverlap.AddDynamic(this, &AArrowBullet::OnHit);
	}
}

void AArrowBullet::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Cast<ACharacterBase>(OtherActor)->ReciveAttack(Damage);
}

void AArrowBullet::SetDamage(float ReciveDamage)
{
	Damage = ReciveDamage;
}

void AArrowBullet::Fire()
{

}

