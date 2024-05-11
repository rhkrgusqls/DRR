// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillElements/DRRPlayerProjectileProto.h"
#include "CharacterBase/CharacterBase.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Utilities/UtilityList.h"

// Sets default values
ADRRPlayerProjectileProto::ADRRPlayerProjectileProto()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MissileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MissileMesh"));
	RootComponent = MissileMesh;
    MissileMesh->SetStaticMesh(Mesh);

    Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));

    Trigger->SetCollisionProfileName(TEXT("PlayerAttack"));
    Trigger->SetSphereRadius(50.0f);
    Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADRRPlayerProjectileProto::OnOverlapBegin);

    // Create a projectile movement component
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->SetUpdatedComponent(MissileMesh);
    ProjectileMovement->InitialSpeed = 3000.0f;
    ProjectileMovement->MaxSpeed = 3000.0f;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->ProjectileGravityScale = 0.0f;

}

// Called when the game starts or when spawned
void ADRRPlayerProjectileProto::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADRRPlayerProjectileProto::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADRRPlayerProjectileProto::Init(AActor* user, float damage)
{
    User = Cast<ACharacterBase>(user);
    Damage = damage;
}

void ADRRPlayerProjectileProto::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ACharacterBase* Temp = Cast<ACharacterBase>(OtherActor);
    Temp->ReciveAttack(Damage);

    CLog::Log("MissileDestroy");
    CLog::Log(OtherActor->GetName());

    Destroy();
}


