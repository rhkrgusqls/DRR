// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/EnemyCharacterBase/NormalMonster.h"
#include "EnemyCharacter/Enemy/NormalEnemyData/DBNormalEnemyAnimMongtage.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyCharacter/AIController/NormalAIController.h"

ANormalMonster::ANormalMonster()
{
	AIControllerClass = ANormalAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
ANormalMonster::ANormalMonster(int Type) : AEnemyCharacterBase(Type)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UDBNormalEnemyAnimMongtage> EnemyAnimAssetRef(TEXT("/Game/Blueprints/DataAsset/EnemeyData/NormalEnemyAnimMongtage.NormalEnemyAnimMongtage"));
	UDBNormalEnemyAnimMongtage* EnemyAnimAsset = nullptr;
	EnemyType = Type;
	if (EnemyAnimAssetRef.Succeeded())
	{
		EnemyAnimAsset = EnemyAnimAssetRef.Object;
	}
	if (EnemyAnimAsset)
	{
		//Iterate through the array and access individual settings
		const FEnemyAnimSet& EnemyAnim = EnemyAnimAsset->SEnemyAnim[EnemyType];

		//Access variables from the EnemyData structure
		NormalAttackMontage = EnemyAnim.NormalAttackMontage;
		EnforceAttackMontage = EnemyAnim.EnforceAttackMontage;
		ChargingAttackMontage = EnemyAnim.ChargingAttackMontage;
		KnockbackMontage = EnemyAnim.KnockbackMontage;
		StiffnessMontage = EnemyAnim.StiffnessMontage;
		DeadMontage = EnemyAnim.DeadMontage;
	}
	AIControllerClass = ANormalAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ANormalMonster::BeginPlay()
{
	//GetController()->;
}

