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
    MissileMesh->SetStaticMesh(Mesh);
    MissileMesh->SetCollisionProfileName(TEXT("NoCollision"));

    Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));

    Trigger->SetCollisionProfileName(TEXT("NoCollision"));
    Trigger->SetSphereRadius(50.0f);

	RootComponent = Trigger;
    MissileMesh->SetupAttachment(Trigger);

    Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADRRPlayerProjectileProto::OnOverlapBegin);

    // Create a projectile movement component
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->SetUpdatedComponent(Trigger);
    ProjectileMovement->InitialSpeed = 3000.0f;
    ProjectileMovement->MaxSpeed = 3000.0f;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->ProjectileGravityScale = 0.0f;


}

// Called when the game starts or when spawned
void ADRRPlayerProjectileProto::BeginPlay()
{
	Super::BeginPlay();
    if (HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    }
}

// Called every frame
void ADRRPlayerProjectileProto::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADRRPlayerProjectileProto::Init(AActor* user, float damage)
{
    if (HasAuthority())
    {
        User = Cast<ACharacterBase>(user);
        Damage = damage;
        Trigger->SetCollisionProfileName(TEXT("PlayerProjectile"));

    }
}

void ADRRPlayerProjectileProto::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    if (HasAuthority())
    {
        Explosion();
        Destroy();

    }
}

void ADRRPlayerProjectileProto::Explosion()
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


    isHit = GetWorld()->OverlapMultiByProfile(outOverlapResults, center,  FQuat::Identity, TEXT("PlayerAttack"), FCollisionShape::MakeSphere(detectRadius), collisionParams);
    


    //DebugDraw
    bool isRemaining = false;
    FColor Color = isHit ? FColor::Green : FColor::Red;
    DrawDebugSphere(GetWorld(), center, detectRadius, 16, Color, isRemaining, 3.0f);




    if (isHit)
    {

        CDisplayLog::Log(TEXT("Collide"));
        for (auto& i : outOverlapResults)
        {
            if (i.GetActor())
            {

                ACharacterBase* Temp=Cast< ACharacterBase>(i.GetActor());
                if (Temp != nullptr)
                {
                    Temp->ReciveAttack(Damage);
                }
                
            }
        }
    }

    //드로우 디버그 가능한 상태일때만
    //디버그 용 코드를 출시할때 영향을 주지 않도록 테스트용 빌드에서만 작동하게함
    Destroy();
}


