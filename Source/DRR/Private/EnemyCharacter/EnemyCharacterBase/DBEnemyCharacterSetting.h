#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DBEnemyCharacterSetting.generated.h"

USTRUCT(BlueprintType)
struct FEnemyCharacterSetting
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule")
    float CapsuleSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule")
    float CapsuleHeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule")
    FString CapsuleProfileName;

    // Set Mesh Value-Kwakhyunbin
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
    FVector MeshVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
    FRotator MeshRotator;

    // Set Movement Value-Kwakhyunbin
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool CharacterbOrientRotationToMovement;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    FRotator CharacterRotationRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float CharacterJumpZVelocity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float CharacterAirControl;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float CharacterMaxWalkSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float CharacterMinAnalogWalkSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float CharacterBrakingDecelerationWalking;

    // Set Mesh and Anim BP-Kwakhyunbin
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
    TObjectPtr<class USkeletalMesh> CharacterMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
    TSubclassOf<class UAnimInstance> CharacterAnimBP;
};

UCLASS()
class UDBEnemyCharacterSetting : public UDataAsset
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    TArray<FEnemyCharacterSetting> SEnemyData;
};