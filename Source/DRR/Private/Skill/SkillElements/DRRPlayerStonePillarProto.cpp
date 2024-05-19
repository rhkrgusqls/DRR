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
    // ������ ��ġ�� ������ ����ϴ�.
    FVector ActorLocation = GetActorLocation();
    FVector DownDirection = FVector(0, 0, -1); // �Ʒ� ���������� ����

    // ����ĳ��Ʈ ����� ������ FHitResult ����ü�� �����մϴ�.
    FHitResult HitResult;

    // ����ĳ��Ʈ ����
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, ActorLocation, ActorLocation + (DownDirection * 1000), ECollisionChannel::ECC_GameTraceChannel6); // �浹 ä���� �����Ͽ� ������ �ݸ����� �����ϵ��� ������ �� �ֽ��ϴ�.

    // ����ĳ��Ʈ�� �浹�� ���
    if (bHit)
    {
        // �浹 ������ ��ǥ�� �����մϴ�.
        HitLocation = HitResult.ImpactPoint;
        
        // ����� �������� ���� �浹 ������ �ð������� ǥ���մϴ�.
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


        //Ÿ�̸� ����: (Ÿ���ڵ鷯, ��ü, ������ �Լ�,�����ð�, ���� ����)
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


        //Ÿ�̸� ����: (Ÿ���ڵ鷯, ��ü, ������ �Լ�,�����ð�, ���� ����)
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

