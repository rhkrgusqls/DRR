// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillElements/DRRPlayerChainDiskProto.h"
#include "CharacterBase/CharacterBase.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Utilities/UtilityList.h"

// Sets default values
ADRRPlayerChainDiskProto::ADRRPlayerChainDiskProto()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    DiskMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MissileMesh"));
    DiskMesh->SetStaticMesh(Mesh);
    DiskMesh->SetCollisionProfileName(TEXT("NoCollision"));

    Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));

    Trigger->SetCollisionProfileName(TEXT("PlayerAttack"));
    Trigger->SetSphereRadius(DetectRadius);
    Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADRRPlayerChainDiskProto::OnOverlapBegin);
    RootComponent = Trigger;
    DiskMesh->SetupAttachment(Trigger);
    

    // Create a projectile movement component
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->SetUpdatedComponent(DiskMesh);
    ProjectileMovement->InitialSpeed = 3000.0f;
    ProjectileMovement->MaxSpeed = 3000.0f;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->ProjectileGravityScale = 0.0f;
    DiskState = EDiskState::Init;
    DetectRadius = 600.0f;
    MaxTargetCount = 6;
    
}

// Called when the game starts or when spawned
void ADRRPlayerChainDiskProto::BeginPlay()
{
    Super::BeginPlay();
    DiskState = EDiskState::Init;
    curDeadTime = 0.0f;

}

// Called every frame
void ADRRPlayerChainDiskProto::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    switch (DiskState)
    {
    case EDiskState::Init :
        NoTargetDead(DeltaTime);
        break;

    case EDiskState::FindTarget :
        Guide();
        CheckArrive();
        break;

    case EDiskState::NoTarget:
        CheckExpire();
        FindTarget();

        break;
    default :
        break;

    }

}

void ADRRPlayerChainDiskProto::Init(AActor* user, float damage)
{
    User = Cast<ACharacterBase>(user);
    Damage = damage;
}

void ADRRPlayerChainDiskProto::NoTargetDead(float delta)
{
    if (curDeadTime > DeadTime)
    {
        Destroy();
        return;
    }
    curDeadTime += delta;
}

bool ADRRPlayerChainDiskProto::CheckArrive()
{
    bool Result = FVector::Distance(this->GetActorLocation(), Target->GetActorLocation()) < ArriveThreshold;

    if (Result)
    {
        Cast<ACharacterBase>(Target)->ReciveAttack(Damage);
        DiskState = EDiskState::NoTarget;
        CurTargetCount++;
    }

    return Result;
}

void ADRRPlayerChainDiskProto::CheckExpire()
{
    if (CurTargetCount >= MaxTargetCount)
    {
        Destroy();
    }
}

void ADRRPlayerChainDiskProto::Guide()
{
    if (Target)
    {
        // Ÿ���� ��ġ�� ���ɴϴ�.
        FVector TargetLocation = Target->GetActorLocation();

        // ����ü�� ��ġ�� ���ɴϴ�.
        FVector ProjectileLocation = GetActorLocation();

        // Ÿ�� ���� ���͸� ����ϴ�.
        FVector Direction = (TargetLocation - ProjectileLocation).GetSafeNormal();

        // ����ü�� ���� ���͸� �����Ͽ� �̵��մϴ�.
        ProjectileMovement->Velocity = Direction * ProjectileMovement->GetMaxSpeed();
    }
    else
    {
        DiskState = EDiskState::NoTarget;

    }
}

bool ADRRPlayerChainDiskProto::FindTarget()
{

    ACharacterBase* UserChar = Cast<ACharacterBase>(User);


    //�浹�� �̸��� ����,������ ����:this�� �־� �ڽ��� �浹�Ǵ°� ����
    FCollisionQueryParams collisionParams(SCENE_QUERY_STAT(FindTarget), false, UserChar);

    FHitResult outHitResult;
    TArray<FHitResult> outHitResults;
    TArray<FOverlapResult> outOverlapResults;
    const float detectRadius = DetectRadius;
    bool isHit;

    //������ ���� ��ġ, ������ �������, ĸ��������Ʈ�� ������ũ��
    const FVector center = this->GetActorLocation();
    const FVector start = center + detectRadius * FVector::ForwardVector;
    const FVector end = center + detectRadius * FVector::BackwardVector;



    //ĸ���� �߾���ġ
    FVector capsulePosition = start + (end - start) / 2.0f;


    isHit = GetWorld()->SweepMultiByProfile(outHitResults, start, end, FQuat::Identity,TEXT("PlayerAttack"), FCollisionShape::MakeSphere(detectRadius), collisionParams);
    


    //DebugDraw
    bool isRemaining = false;
    FColor Color = isHit ? FColor::Green : FColor::Red;
     DrawDebugSphere(GetWorld(), center,detectRadius,16, Color, isRemaining, 3.0f);




    if (isHit)
    {

        //�浹����� ���� ������ ���ظ� ������ �Լ� ȣ��
        //�𸮾󿡼� ������ ��� ���͵��� �������� �Դ´ٴ� �����Ͽ� �����Լ�
        //����, �̺�Ʈ, ������Ʈ�ѷ�,������ ����

        AActor* MinActor=nullptr;

        float MinDistance;

        for (auto& i : outHitResults)
        {
            ACharacterBase* Temp;
            if (i.GetActor())
            {
                if (i.GetActor() == Target)
                    continue;
                if (Targeted.Contains(i.GetActor()))
                    continue;
                Temp = Cast< ACharacterBase>(i.GetActor());
                if (Temp != nullptr)
                {

                    if (MinActor == nullptr)



                    {
                        MinActor = i.GetActor();
                        MinDistance = FVector::Distance(i.GetActor()->GetActorLocation(), this->GetActorLocation());
                    }
                    else
                    {
                        if (MinDistance > FVector::Distance(i.GetActor()->GetActorLocation(), this->GetActorLocation()))
                        {

                            MinActor = i.GetActor();

                            MinDistance = FVector::Distance(i.GetActor()->GetActorLocation(), this->GetActorLocation());
                        }
                    }




                }
            }
        }
        if (MinActor == nullptr)
        {
            for (auto& i : outHitResults)
            {
                ACharacterBase* Temp;
                if (i.GetActor())
                {
                    if (i.GetActor() == Target)
                        continue;
                    Temp = Cast< ACharacterBase>(i.GetActor());
                    if (Temp != nullptr)
                    {

                        if (MinActor == nullptr)
                        {
                            MinActor = i.GetActor();
                            MinDistance = FVector::Distance(i.GetActor()->GetActorLocation(), this->GetActorLocation());
                        }
                        else
                        {
                            if (MinDistance > FVector::Distance(i.GetActor()->GetActorLocation(), this->GetActorLocation()))
                            {

                                MinActor = i.GetActor();

                                MinDistance = FVector::Distance(i.GetActor()->GetActorLocation(), this->GetActorLocation());
                            }
                        }




                    }
                }
            }
        }
        if (MinActor!=nullptr)
        {
            Target = MinActor;
            DiskState = EDiskState::FindTarget;

            return true;

        }

    }

    //��ο� ����� ������ �����϶���
    //����� �� �ڵ带 ����Ҷ� ������ ���� �ʵ��� �׽�Ʈ�� ���忡���� �۵��ϰ���
    Destroy();
    return false;
}

void ADRRPlayerChainDiskProto::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    CDisplayLog::Log(TEXT("DiskCollide"));
    Target = OtherActor;
    Trigger->SetCollisionProfileName(TEXT("NoCollision"));
    DiskState = EDiskState::FindTarget;

}


