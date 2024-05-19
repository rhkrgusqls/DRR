// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillElements/DRRPlayerStonePillarProto.h"

#include "Components/CapsuleComponent.h"
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
    RootComponent = PillarMesh;
    PillarMesh->SetStaticMesh(Mesh);

    CollisionChannelName=PillarMesh->GetCollisionProfileName().ToString();
    PillarMesh->SetCollisionProfileName(TEXT("NoCollision"));
    PillarMesh->SetVisibility(false);
    // Bind hit event
    OnActorBeginOverlap.AddDynamic(this, &ADRRPlayerStonePillarProto::OnPillarHit);
 


}

// Called when the game starts or when spawned
void ADRRPlayerStonePillarProto::BeginPlay()
{
	Super::BeginPlay();
    if (HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    }
    SetFloor();
    SetTimer();
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
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, ActorLocation, ActorLocation + (DownDirection * 1000), ECollisionChannel::ECC_GameTraceChannel6); // 충돌 채널을 조정하여 적절한 콜리전에 반응하도록 설정할 수 있습니다.

    // 레이캐스트가 충돌한 경우
    if (bHit)
    {
        // 충돌 지점의 좌표를 저장합니다.
        HitLocation = HitResult.ImpactPoint;
        
        // 디버그 렌더링을 통해 충돌 지점을 시각적으로 표시합니다.
        DrawDebugSphere(GetWorld(), HitLocation, 10, 12, FColor::Red, false, 5);
        SetActorLocation(HitLocation);
    }



}

// Called every frame
void ADRRPlayerStonePillarProto::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADRRPlayerStonePillarProto::Init(AActor* user, float damage)
{
    User = user;
    Damage = damage;
}

void ADRRPlayerStonePillarProto::SetTimer()
{
    float AriseDelay=DelayTime;
    if (AriseDelay > 0.0f)
    {


        //타이머 설정: (타임핸들러, 객체, 실행할 함수,지연시간, 루프 여부)
        GetWorld()->GetTimerManager().SetTimer(RiseupTimerHandle, this, &ADRRPlayerStonePillarProto::Arise, AriseDelay, false);
    }

}

void ADRRPlayerStonePillarProto::Arise()
{

    PillarMesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);
    PillarMesh->SetVisibility(true);
    PillarMesh->AddRelativeLocation(FVector::UpVector * 100.0f);
    float ExpireDelay = ExpireTime;
    if (ExpireDelay > 0.0f)
    {


        //타이머 설정: (타임핸들러, 객체, 실행할 함수,지연시간, 루프 여부)
        GetWorld()->GetTimerManager().SetTimer(RiseupTimerHandle, this, &ADRRPlayerStonePillarProto::Expire, ExpireDelay, false);
    }
}

void ADRRPlayerStonePillarProto::Expire()
{

    Destroy();

}

void ADRRPlayerStonePillarProto::OnPillarHit(AActor* SelfActor, AActor* OtherActor)
{
    if (Hitted.Contains(OtherActor))
    {
        return;
    }
    else
    {
        Hitted.Add(OtherActor);
        ACharacterBase* Temp = Cast<ACharacterBase>(OtherActor);
        CDisplayLog::Log(TEXT("PillarHit"));

        const float defaultDamage = 15.0f;
        float damageResult = defaultDamage * Damage;
        if (Temp != nullptr)
        {
            Temp->ReciveAttack(damageResult);

        }

    }
}

