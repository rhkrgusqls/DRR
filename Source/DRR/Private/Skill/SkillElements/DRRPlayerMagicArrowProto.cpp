// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillElements/DRRPlayerMagicArrowProto.h"
#include "CharacterBase/CharacterBase.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Utilities/UtilityList.h"

// Sets default values
ADRRPlayerMagicArrowProto::ADRRPlayerMagicArrowProto()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    MissileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MissileMesh"));
    MissileMesh->SetStaticMesh(Mesh);
    MissileMesh->SetCollisionProfileName(TEXT("NoCollision"));

    Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));

    Trigger->SetCollisionProfileName(TEXT("PlayerAttack"));
    Trigger->SetSphereRadius(50.0f);
    Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADRRPlayerMagicArrowProto::OnOverlapBegin);
    RootComponent = Trigger;
    MissileMesh->SetupAttachment(Trigger);

    // Create a projectile movement component
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->SetUpdatedComponent(Trigger);
    ProjectileMovement->InitialSpeed = 3000.0f;
    ProjectileMovement->MaxSpeed = 3000.0f;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->ProjectileGravityScale = 0.0f;

}

// Called when the game starts or when spawned
void ADRRPlayerMagicArrowProto::BeginPlay()
{
    Super::BeginPlay();
    ArrowState = EArrowState::Init;

    Trigger->SetCollisionProfileName(TEXT("NoCollision"));

    ArrowInitialSpeed = ProjectileMovement->InitialSpeed;
    ArrowMaxSpeed = ProjectileMovement->MaxSpeed;

    ProjectileMovement->MaxSpeed = 0.0f;
    ProjectileMovement->InitialSpeed = 0.0f;
    ProjectileMovement->Velocity=FVector::ZeroVector;
    SetTimer();
}

// Called every frame
void ADRRPlayerMagicArrowProto::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    


}

void ADRRPlayerMagicArrowProto::Init(AActor* user, float damage)
{
    User = Cast<ACharacterBase>(user);
    Damage = damage;
}

void ADRRPlayerMagicArrowProto::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ACharacterBase* Temp = Cast<ACharacterBase>(OtherActor);
    Temp->ReciveAttack(Damage);

    CLog::Log("MissileDestroy");
    CLog::Log(OtherActor->GetName());

    Destroy();
}

void ADRRPlayerMagicArrowProto::SetTimer()
{
    float  fireTime = FireDelay;
    if (fireTime > 0.0f)
    {


        //타이머 설정: (타임핸들러, 객체, 실행할 함수,지연시간, 루프 여부)
        GetWorld()->GetTimerManager().SetTimer(TimeHandler, this, &ADRRPlayerMagicArrowProto::Eject, fireTime, false);
    }
    else
    {
        Eject();
    }

}

void ADRRPlayerMagicArrowProto::Eject()
{
    CDisplayLog::Log(TEXT("Eject"));
    ArrowState = EArrowState::Eject;

    Trigger->SetCollisionProfileName(TEXT("PlayerAttack"));

    ProjectileMovement->InitialSpeed = ArrowInitialSpeed;
    ProjectileMovement->MaxSpeed = ArrowMaxSpeed;
    ProjectileMovement->Velocity = GetActorForwardVector()*3000;
}


