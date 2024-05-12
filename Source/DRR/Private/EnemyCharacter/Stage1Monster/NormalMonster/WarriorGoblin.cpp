#include "EnemyCharacter/Stage1Monster/NormalMonster/WarriorGoblin.h"
#include "GameFramework/Actor.h"


AWarriorGoblin::AWarriorGoblin() : AMeleeMonsterBase(0)
{
    // Constructor for AWarriorGoblin class
    // Add any necessary initialization code here
    RightWeaponHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
    LeftWeaponHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxx"));

    MaxComboCount = 3;
}

void AWarriorGoblin::BeginPlay()
{
    Super::BeginPlay();

    // Create the hitbox between bones when the game starts
    CreateHitBoxBetweenBones(TEXT("FX_Trail_R_02"),TEXT("FX_Trail_R_01"),TEXT("FX_Trail_L_02"),TEXT("FX_Trail_L_01"));

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

void AWarriorGoblin::SetCollision()
{
    if (ComboCount==2)
    {
        LeftWeaponHitBox->SetCollisionProfileName(TEXT("EnemyAttack"));
        RightWeaponHitBox->SetCollisionProfileName(TEXT("EnemyAttack"));
    }
    if (ComboCount == 3)
    {
        LeftWeaponHitBox->SetCollisionProfileName(TEXT("EnemyAttack"));
        RightWeaponHitBox->SetCollisionProfileName(TEXT("EnemyAttack"));
    }

}


