// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillElements/DRRPlayerMiniProjectileProto.h"

#include "CharacterBase/CharacterBase.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Utilities/UtilityList.h"

// Sets default values
ADRRPlayerMiniProjectileProto::ADRRPlayerMiniProjectileProto()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    MissileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MissileMesh"));
    MissileMesh->SetStaticMesh(Mesh);
    //MissileMesh->SetCollisionProfileName(TEXT("FindWall"));
    MissileMesh->SetCollisionProfileName(TEXT("FindWall"));
    MissileMesh->OnComponentHit.AddDynamic(this, &ADRRPlayerMiniProjectileProto::OnStaticMeshHit);
    MissileMesh->SetEnableGravity(false);

    Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));

    Trigger->SetCollisionProfileName(TEXT("PlayerProjectile"));
    Trigger->SetSphereRadius(50.0f);

    RootComponent = MissileMesh;
    Trigger->SetupAttachment(MissileMesh);

    Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADRRPlayerMiniProjectileProto::OnOverlapBegin);
    // Create a projectile movement component
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->SetUpdatedComponent(RootComponent);
    ProjectileMovement->InitialSpeed = 3000.0f;
    ProjectileMovement->MaxSpeed = 3000.0f;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->ProjectileGravityScale = 0.0f;

    SetActorEnableCollision(false);

}

// Called when the game starts or when spawned
void ADRRPlayerMiniProjectileProto::BeginPlay()
{
    Super::BeginPlay();
    SetReplicates(true);
    SetReplicateMovement(true);

}

// Called every frame
void ADRRPlayerMiniProjectileProto::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ADRRPlayerMiniProjectileProto::Init(AActor* user, float damage)
{

    User = Cast<ACharacterBase>(user) == nullptr ? Cast<ACharacterBase>(user) : nullptr;
    Damage = damage;
    //Trigger->SetCollisionProfileName(TEXT("PlayerProjectile"));
    //MissileMesh->SetCollisionProfileName(TEXT("FindWall"));
    SetActorEnableCollision(true);
}

void ADRRPlayerMiniProjectileProto::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ACharacterBase* Temp = Cast< ACharacterBase>(OtherActor);
    if (Temp != nullptr)
    {
        if (HasAuthority())
        {

            Temp->ReciveAttack(Damage);
        }
    }


    HitEffect();
    Destroy();
}

void ADRRPlayerMiniProjectileProto::OnStaticMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

    HitEffect();
    Destroy();
}

void ADRRPlayerMiniProjectileProto::OnStaticMeshOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    CDisplayLog::Log(TEXT("Overlap %s"), *(OtherActor->GetName()));
    CDisplayLog::Log(TEXT("Overlap %s"), *(OtherComp->GetName()));


    HitEffect();
    Destroy();
}

void ADRRPlayerMiniProjectileProto::HitEffect()
{
}

