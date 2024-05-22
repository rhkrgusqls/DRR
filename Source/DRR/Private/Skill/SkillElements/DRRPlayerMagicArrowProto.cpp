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

    Trigger->SetCollisionProfileName(TEXT("PlayerProjectile"));
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


    SetActorEnableCollision(false);
}

// Called when the game starts or when spawned
void ADRRPlayerMagicArrowProto::BeginPlay()
{
    Super::BeginPlay();
    ArrowState = EArrowState::Init;


    ArrowInitialSpeed = ProjectileMovement->InitialSpeed;
    ArrowMaxSpeed = ProjectileMovement->MaxSpeed;

    ProjectileMovement->MaxSpeed = 0.0f;
    ProjectileMovement->InitialSpeed = 0.0f;
    ProjectileMovement->Velocity=FVector::ZeroVector;

    Trigger->SetCollisionProfileName(TEXT("NoCollision"));
    if (HasAuthority())
    {

        SetReplicates(true);
        SetReplicateMovement(true);
    }
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
    SetActorEnableCollision(true);
}

void ADRRPlayerMagicArrowProto::SetDelay(float delay)
{
    FireDelay = delay;
    SetTimer();
}

void ADRRPlayerMagicArrowProto::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OverlappedComponent && OverlappedComponent->GetCollisionProfileName() == TEXT("Player"))
    {
        return;
    }
    Explosion();


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
    ArrowState = EArrowState::Eject;

    Trigger->SetCollisionProfileName(TEXT("PlayerProjectile"));

    ProjectileMovement->InitialSpeed = ArrowInitialSpeed;
    ProjectileMovement->MaxSpeed = ArrowMaxSpeed;
    ProjectileMovement->Velocity = GetActorForwardVector()*3000;
}

void ADRRPlayerMagicArrowProto::Explosion()
{
    //충돌에 이름을 붙임,무시할 액터:this를 넣어 자신이 충돌되는걸 방지
    FCollisionQueryParams collisionParams(SCENE_QUERY_STAT(FindTarget), false, this);

    FHitResult outHitResult;
    TArray<FHitResult> outHitResults;
    TArray<FOverlapResult> outOverlapResults;
    const float detectRadius = 150.0f;
    bool isHit;

    //액터의 현재 위치, 액터의 정면백터, 캡슐컴포넌트의 반지름크기
    const FVector center = this->GetActorLocation();
    const FVector start = center + detectRadius * FVector::ForwardVector;
    const FVector end = center + detectRadius * FVector::BackwardVector;



    //캡슐의 중앙위치
    FVector capsulePosition = start + (end - start) / 2.0f;


    isHit = GetWorld()->OverlapMultiByProfile(outOverlapResults, center, FQuat::Identity, TEXT("PlayerAttack"), FCollisionShape::MakeSphere(detectRadius), collisionParams);



    //DebugDraw
    bool isRemaining = false;
    FColor Color = isHit ? FColor::Green : FColor::Red;
    DrawDebugSphere(GetWorld(), center, detectRadius, 16, Color, isRemaining, 3.0f);




    if (isHit)
    {

        CDisplayLog::Log(TEXT("Collide"));
        for (auto& i : outOverlapResults)
        {

            if (i.GetComponent() && i.GetComponent()->GetCollisionProfileName() == TEXT("Player"))
            {
                continue;
            }


            if (i.GetActor())
            {




                ACharacterBase* Temp = Cast< ACharacterBase>(i.GetActor());
                
                if (Temp != nullptr)
                {
                    if (HasAuthority())
                    {
                        Temp->ReciveAttack(Damage);

                    }
                }

            }
        }
    }

    //드로우 디버그 가능한 상태일때만
    //디버그 용 코드를 출시할때 영향을 주지 않도록 테스트용 빌드에서만 작동하게함
    Destroy();
}


