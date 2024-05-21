// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillElements/DRRPlayerStonePillarProto.h"

#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Engine/DamageEvents.h"
#include "CharacterBase/CharacterBase.h"

#include "Utilities/UtilityList.h"
// Sets default values
ADRRPlayerStonePillarProto::ADRRPlayerStonePillarProto()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    PillarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PillarMesh"));
    PillarMesh->SetStaticMesh(Mesh);
    PillarMesh->SetCollisionProfileName(TEXT("NoCollision"));

    Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

    Trigger->SetCollisionProfileName(TEXT("NoCollision"));
    Trigger->SetBoxExtent(FVector(40.0f, 40.0f, 100.0f));
    Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADRRPlayerStonePillarProto::OnOverlapBegin);
    RootComponent = Trigger;
    PillarMesh->SetupAttachment(Trigger);


    DelayTime=1.0f;

    RisingTime=0.3f;
    ExpireTime=0.5f;

    Damage=5.0f;


}

// Called when the game starts or when spawned
void ADRRPlayerStonePillarProto::BeginPlay()
{
	Super::BeginPlay();
    PillarState = EPillarState::Init;
    //PillarMesh->SetVisibility(false);
    if (HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    }
    SetFloor();
    SetRisingTimer();
}

void ADRRPlayerStonePillarProto::SetFloor()
{
    FVector HitLocation;
    // 액터의 위치와 방향을 얻습니다.
    FVector ActorLocation = GetActorLocation();
    FVector DownDirection = FVector(0, 0, -1); // 아래 방향으로의 벡터

    // 레이캐스트 결과를 저장할 FHitResult 구조체를 정의합니다.
    FHitResult HitResult;
    // 레이캐스트 수행
    bool bHit = GetWorld()->LineTraceSingleByProfile(HitResult, ActorLocation, ActorLocation + (DownDirection * 1000), TEXT("FindWall")); // 충돌 채널을 조정하여 적절한 콜리전에 반응하도록 설정할 수 있습니다.

    // 레이캐스트가 충돌한 경우
    if (bHit)
    {
        CDisplayLog::Log(TEXT("SetFloor"));
        // 충돌 지점의 좌표를 저장합니다.
        HitLocation = HitResult.ImpactPoint;
        
        SetActorLocation(HitLocation);
        FVector Temp = GetActorLocation();
        Temp.Z -= Trigger->GetUnscaledBoxExtent().Z * 1.0f;
        SetActorLocation(Temp);
    }
    else
    {
        FVector Temp = GetActorLocation();
        Temp.Z -= Trigger->GetUnscaledBoxExtent().Z * 2.0f;
        SetActorLocation(Temp);

    }
    OriginPos = GetActorLocation();



}

// Called every frame
void ADRRPlayerStonePillarProto::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    switch (PillarState)
    {
        case EPillarState::Init :
            break;
        case EPillarState::Ambush :
            break;

        case EPillarState::Rising:
            Rising(DeltaTime);

            break;
        case EPillarState::Stay:

            break;
        case EPillarState::Expire:
            Expiring(DeltaTime);
            break;
        default :
            break;
    }

}

void ADRRPlayerStonePillarProto::Init(AActor* user, float damage)
{
    User = user;
    Damage = damage;
}

void ADRRPlayerStonePillarProto::SetRisingTimer()
{
    float AriseDelay=DelayTime;
    if (AriseDelay > 0.0f)
    {


        //타이머 설정: (타임핸들러, 객체, 실행할 함수,지연시간, 루프 여부)
        GetWorld()->GetTimerManager().SetTimer(RiseupTimerHandle, this, &ADRRPlayerStonePillarProto::Arise, AriseDelay, false);
    }

}

void ADRRPlayerStonePillarProto::SetExpireTimer()
{
    
    if (ExpireTime > 0.0f)
    {


        //타이머 설정: (타임핸들러, 객체, 실행할 함수,지연시간, 루프 여부)
        GetWorld()->GetTimerManager().SetTimer(RiseupTimerHandle, this, &ADRRPlayerStonePillarProto::Expire, ExpireTime, false);
    }

}

void ADRRPlayerStonePillarProto::Arise()
{
    PillarState = EPillarState::Rising;
    Trigger->SetCollisionProfileName(TEXT("PlayerProjectile"));
    PillarMesh->SetVisibility(true);
    
}

void ADRRPlayerStonePillarProto::Rising(float delta)
{
    float dist = (Trigger->GetUnscaledBoxExtent().Z*2.5f) / RisingTime;
    FVector NowPos = GetActorLocation();
    NowPos.Z += dist * delta;
    if (NowPos.Z >= OriginPos.Z + Trigger->GetScaledBoxExtent().Z)
    {
        NowPos.Z = OriginPos.Z + Trigger->GetScaledBoxExtent().Z;
        PillarState = EPillarState::Stay;
        SetExpireTimer();

    }
    SetActorLocation(NowPos);


}

void ADRRPlayerStonePillarProto::Expiring(float delta)
{
    float dist = (Trigger->GetUnscaledBoxExtent().Z*2.5f) / RisingTime;
    FVector NowPos = GetActorLocation();
    NowPos.Z -= dist * delta;
    if (NowPos.Z <= OriginPos.Z )
    {
        PillarState = EPillarState::Init;
        Destroy();

    }
    SetActorLocation(NowPos);
    

}

void ADRRPlayerStonePillarProto::Expire()
{
    PillarState = EPillarState::Expire;
}

void ADRRPlayerStonePillarProto::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ACharacterBase* Temp = Cast<ACharacterBase>(OtherActor);
    if (OtherActor == User)
        return;

    if (OverlappedComponent && OverlappedComponent->GetCollisionProfileName() == TEXT("Player"))
    {
        return;
    }
    if (Temp != nullptr)
    {
        CDisplayLog::Log(TEXT("Hitted : %s"), *(OtherActor->GetName()));
        if (Hitted.Contains(OtherActor))
        {
            return;
        }

        const float defaultDamage = 15.0f;
        float damageResult = defaultDamage * Damage;

        if (HasAuthority())
        {
            Temp->ReciveAttack(damageResult);

        }
        Hitted.Add(OtherActor);
       
    }
}
