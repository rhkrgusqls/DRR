#include "EnemyCharacter/Stage1Monster/NormalMonster/WarriorGoblin.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/BoxComponent.h"

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
    BoneName1 = TEXT("FX_Trail_R_01");
    BoneName2 = TEXT("FX_Trail_R_02");

    // Get the positions of the bones
    BonePosition1 = SkeletalMeshComp->GetSocketLocation(BoneName1);
    BonePosition2 = SkeletalMeshComp->GetSocketLocation(BoneName2);

    // Calculate the midpoint and direction between the bones
    MidPoint = (BonePosition1 + BonePosition2) / 2;
    Direction = (BonePosition2 - BonePosition1).GetSafeNormal();

    // Set the size of the rectangular hitbox
    BoxExtent = FVector(10.0f, 10.0f, 10.0f);

    // Create and set up the collision box
    HitBox = NewObject<UBoxComponent>(this);
    if (HitBox)
    {
        // Configure HitBox properties
        HitBox->SetBoxExtent(BoxExtent);
        HitBox->SetWorldLocationAndRotation(MidPoint, Direction.Rotation());
        HitBox->AttachToComponent(SkeletalMeshComp, FAttachmentTransformRules::KeepWorldTransform);

        // Set the desired collision profile
        HitBox->SetCollisionProfileName(TEXT("BlockAll"));

        // Register the component to activate it
        HitBox->RegisterComponent();

        // Enable debug rendering
        HitBox->SetHiddenInGame(false);
    }
}

void AWarriorGoblin::BeginPlay()
{
    Super::BeginPlay();

    // Create the hitbox between bones when the game starts
    CreateHitBoxBetweenBones();
}