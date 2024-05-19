// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/AB_ItemBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Interface/DRRGetItem.h"
#include "Engine/AssetManager.h"

// Sets default values
AAB_ItemBox::AAB_ItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);
	//Effect->bAutoActivate = false;
	//Effect->SetupAttachment(Trigger);

	Trigger->SetCollisionProfileName(TEXT("ABTrigger"));
	Trigger->SetBoxExtent(FVector(40.0f, 45.0f, 30.0f));
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AAB_ItemBox::OnOverlapBegin);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Game/ProtoTypeAsset/DownLoadAsset/PolygonFantasyRivals/Meshes/Props/SM_Prop_Pouch_01.SM_Prop_Pouch_01"));
	if (BoxMeshRef.Object)
	{
		Mesh->SetStaticMesh(BoxMeshRef.Object);
		Mesh->SetRelativeScale3D(FVector(3.0f, 7.0f, 3.0f));
		Mesh->SetRelativeLocation(FVector(0.0f, -30.0f, 0.0f));
		Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	}

	//static ConstructorHelpers::FObjectFinder<UParticleSystem> EffectRef(TEXT(""));
	//if (EffectRef.Object)
	//{
	//	Effect->SetTemplate(EffectRef.Object);
	//	Effect->bAutoActivate = false;
	//}
}

void AAB_ItemBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ItemData == nullptr)
	{
		Destroy();
		return;
	}

	//Effect->OnSystemFinished.AddDynamic(this, &AABItemBox::OnEffectFinished);


	IDRRGetItem* OverlappingActor = Cast<IDRRGetItem>(OtherActor);
	if (OverlappingActor)
	{
		OverlappingActor->TakeItem(ItemData);
	}

	Destroy();
}

//void AAB_ItemBox::OnEffectFinished(UParticleSystemComponent* Psystem)
//{
//	Destroy();
//}

void AAB_ItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	int ID = FMath::RandRange(10, 15);
	int Amount = FMath::RandRange(10, 15);

	UAssetManager& Manager = UAssetManager::Get();
	TArray<FPrimaryAssetId> AssetIds;
	Manager.GetPrimaryAssetIdList(TEXT("DA_ItemData"), AssetIds);

	ensure(AssetIds.Num() > 0);

	int32 RandomIndex = FMath::RandRange(0, 15);
	FSoftObjectPtr AssetPtr(Manager.GetPrimaryAssetPath(AssetIds[RandomIndex]));
	if (AssetPtr.IsPending())
	{
		AssetPtr.LoadSynchronous();
	}
	ItemData = Cast<UDA_ItemData>(AssetPtr.Get());

}

// Called when the game starts or when spawned
void AAB_ItemBox::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAB_ItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

