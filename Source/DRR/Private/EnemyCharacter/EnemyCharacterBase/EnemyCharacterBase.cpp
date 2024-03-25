// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/EnemyCharacterBase/EnemyCharacterBase.h"
#include "DBEnemyCharacterSetting.h"
#include "Components/CapsuleComponent.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyCharacterBase::AEnemyCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDBEnemyCharacterSetting> EnemyDataAssetRef(TEXT("/Game/Blueprints/DataAsset/EnemeyData/EnemeyCharacter.EnemeyCharacter"));
	UDBEnemyCharacterSetting* EnemyDataAsset = nullptr;

	if (EnemyDataAssetRef.Succeeded())
	{
		EnemyDataAsset = EnemyDataAssetRef.Object;
	}
	if (EnemyDataAsset)
	{
		// Iterate through the array and access individual settings
		for (const FEnemyCharacterSetting& EnemyData : EnemyDataAsset->SEnemyData)
		{
			// Access variables from the EnemyData structure
			EnemyName = EnemyData.Name;
			CapsuleSize = EnemyData.CapsuleSize;
			CapsuleHeight = EnemyData.CapsuleHeight;
			CapsuleProfileName = EnemyData.CapsuleProfileName;
			MeshVector = EnemyData.MeshVector;
			MeshRotator = EnemyData.MeshRotator;
			CharacterbOrientRotationToMovement = EnemyData.CharacterbOrientRotationToMovement;
			CharacterRotationRate = EnemyData.CharacterRotationRate;
			CharacterJumpZVelocity = EnemyData.CharacterJumpZVelocity;
			CharacterAirControl = EnemyData.CharacterAirControl;
			CharacterMaxWalkSpeed = EnemyData.CharacterMaxWalkSpeed;
			CharacterMinAnalogWalkSpeed = EnemyData.CharacterMinAnalogWalkSpeed;
			CharacterBrakingDecelerationWalking = EnemyData.CharacterBrakingDecelerationWalking;
			CharacterMesh = EnemyData.CharacterMesh;
			CharacterAnimBP = EnemyData.CharacterAnimBP;
		}
	}

	// Create Capsule-Kwakhyunbin
	GetCapsuleComponent()->InitCapsuleSize(CapsuleSize, CapsuleHeight);
	GetCapsuleComponent()->SetCollisionProfileName(FName(*CapsuleProfileName));

	// Set Mesh-Kwakhyunbin
	GetMesh()->SetRelativeLocationAndRotation(MeshVector, MeshRotator);
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	//Set Movement Default-Kwakhyunbin
	GetCharacterMovement()->bOrientRotationToMovement = CharacterbOrientRotationToMovement;
	GetCharacterMovement()->RotationRate = CharacterRotationRate;
	GetCharacterMovement()->JumpZVelocity = CharacterJumpZVelocity;
	GetCharacterMovement()->AirControl = CharacterAirControl;
	GetCharacterMovement()->MaxWalkSpeed = CharacterMaxWalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = CharacterMinAnalogWalkSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = CharacterBrakingDecelerationWalking;

	//Set Rotation Remit-Kwakhyunbin
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//Set Mesh and Anim BP-Kwakhyunbin
	GetMesh()->SetSkeletalMesh(CharacterMesh);
	GetMesh()->SetAnimInstanceClass(CharacterAnimBP);
}

void AEnemyCharacterBase::OnPerception(AActor* Actor, FAIStimulus stimulus)
{
}
