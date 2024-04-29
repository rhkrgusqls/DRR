#include "EnemyCharacter/Stage1Monster/NormalMonster/WarriorGoblin.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"

AWarriorGoblin::AWarriorGoblin()
{
    // Constructor for AWarriorGoblin class
    // Add any necessary initialization code here
}

void AWarriorGoblin::CreateHitBoxBetweenBones()
{
    // Reference to Skeletal Mesh Component
    SkeletalMeshComp = FindComponentByClass<USkeletalMeshComponent>();
    if (!SkeletalMeshComp)
    {
        UE_LOG(LogTemp, Warning, TEXT("SkeletalMeshComponent not found."));
        return;
    }

    // Names of the bones
    BoneName1 = TEXT("FX_Trail_R_02");
    BoneName2 = TEXT("FX_Trail_R_01");

    // Get the positions of the bones
    BonePosition1 = SkeletalMeshComp->GetSocketLocation(BoneName1);
    BonePosition2 = SkeletalMeshComp->GetSocketLocation(BoneName2);

    // Calculate the midpoint and direction between the bones
    MidPoint = (BonePosition1 + BonePosition2) / 2;
    Direction = (BonePosition2 - BonePosition1).GetSafeNormal();

    FVector DifferenceRo = BonePosition1 - BonePosition2;

    FRotator RotationR = DifferenceRo.Rotation();

    FVector Difference = BonePosition1 - BonePosition2;


    float Distance = Difference.Size();

    // Set the size of the rectangular hitbox
    BoxExtent = FVector(Distance, 10.0f, 20.f);




    // Create and set up the collision box
    RightWeaponHitBox = NewObject<UBoxComponent>(this);
    if (RightWeaponHitBox)
    {
        // Configure HitBox properties
        RightWeaponHitBox->SetBoxExtent(BoxExtent);
        RightWeaponHitBox->AttachToComponent(SkeletalMeshComp, FAttachmentTransformRules::KeepWorldTransform);


        RightWeaponHitBox->AttachToComponent(SkeletalMeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "FX_Trail_R_01");

        RightWeaponHitBox->SetWorldLocation(MidPoint);
        RightWeaponHitBox->SetWorldRotation(GetRotationForBone(BonePosition1,BonePosition2));//RotationR);

        // Set the desired collision profile
        RightWeaponHitBox->SetCollisionProfileName(TEXT("BlockAll"));

        // Register the component to activate it
        RightWeaponHitBox->RegisterComponent();

        // Enable debug rendering
        RightWeaponHitBox->SetHiddenInGame(false);
    }

    // Reference to Skeletal Mesh Component
    SkeletalMeshComp2 = FindComponentByClass<USkeletalMeshComponent>();
    if (!SkeletalMeshComp2)
    {
        UE_LOG(LogTemp, Warning, TEXT("SkeletalMeshComponent not found."));
        return;
    }

    // Names of the bones
    BoneName3 = TEXT("FX_Trail_L_02");
    BoneName4 = TEXT("FX_Trail_L_01");

    // Get the positions of the bones
    BonePosition3 = SkeletalMeshComp->GetSocketLocation(BoneName3);
    BonePosition4 = SkeletalMeshComp->GetSocketLocation(BoneName4);

    // Calculate the midpoint and direction between the bones
    MidPoint = (BonePosition3 + BonePosition4) / 2;
    Direction = (BonePosition3 - BonePosition4).GetSafeNormal();

    FVector DifferenceRo2 = BonePosition3 - BonePosition4;

    FRotator RotationR2 = DifferenceRo2.Rotation();

    FVector Difference2 = BonePosition3 - BonePosition4;


    float Distance2 = Difference2.Size();

    // Set the size of the rectangular hitbox
    BoxExtent = FVector(Distance2, 10.0f, 20.0f);




    // Create and set up the collision box
    LeftWeaponHitBox = NewObject<UBoxComponent>(this);
    if (LeftWeaponHitBox)
    {
        // Configure HitBox properties
        LeftWeaponHitBox->SetBoxExtent(BoxExtent);
        LeftWeaponHitBox->AttachToComponent(SkeletalMeshComp, FAttachmentTransformRules::KeepWorldTransform);


        LeftWeaponHitBox->AttachToComponent(SkeletalMeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "FX_Trail_L_01");

        LeftWeaponHitBox->SetWorldLocation(MidPoint);
        LeftWeaponHitBox->SetWorldRotation(GetRotationForBone(BonePosition3, BonePosition4));//RotationR);

        // Set the desired collision profile
        LeftWeaponHitBox->SetCollisionProfileName(TEXT("BlockAll"));

        // Register the component to activate it
        LeftWeaponHitBox->RegisterComponent();

        // Enable debug rendering
        LeftWeaponHitBox->SetHiddenInGame(false);
    }
}

void AWarriorGoblin::BeginPlay()
{
    Super::BeginPlay();

    FTimerHandle TimerHandle;

    // Create the hitbox between bones when the game starts
    CreateHitBoxBetweenBones();
}

void AWarriorGoblin::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (RightWeaponHitBox)
    {
        
        FVector BoxLocation = RightWeaponHitBox->GetComponentLocation();
        FRotator BoxRotation = RightWeaponHitBox->GetComponentRotation();

     
        FVector BoxExtent2= RightWeaponHitBox->GetScaledBoxExtent();

       
        FColor BoxColor = FColor::Red; 
        float LifeTime = 0.1f;
        bool bPersistentLines = false;
        float Thickness = 1.0f;
        
        DrawDebugBox(
            GetWorld(),
            BoxLocation, 
            BoxExtent2, 
            BoxRotation.Quaternion(), 
            BoxColor,
            bPersistentLines, 
            LifeTime,
            0, 
            Thickness
        );
    }

}

FRotator AWarriorGoblin::GetRotationForBone(FVector BoneX, FVector BoneY)
{
    FVector Direction3 = BoneX - BoneY;
    Direction3.Normalize();

    FRotator Rotation2 = Direction3.Rotation();
    return Rotation2;
}
