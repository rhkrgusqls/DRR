
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_EffectData.generated.h"



//���, ���ݽ�, Ÿ�ݽ�, �ǰݽ�
UENUM()
enum class EPassiveType : uint8
{
	Auto=0,
	Attack,
	Damage,
	Hit
};

//ȿ���� ���� Ÿ��. �ð�, ���Ƚ��, ����
UENUM()
enum class EExpirationType : uint8
{
	Duration,
	Usage,
	DurationOrUse,
	Permanent
};


UENUM()
enum class EPassiveStateType : uint8
{

	buff,
	debuff
};


UCLASS()
class DRR_API UDA_EffectData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = Section)
	FString PassiveName;


	UPROPERTY(EditAnywhere, Category = Section)
	FString PassiveDescription;

	//update�� ����
	UPROPERTY(EditAnywhere, Category = Section)
	float PassiveDelay;

	//���ӽð�
	UPROPERTY(EditAnywhere, Category = Section)
	float PassiveDuration;

	//��밡�� Ƚ��
	UPROPERTY(EditAnywhere, Category = Section)
	uint8 UsageCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	EPassiveType UseType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	EExpirationType ExpirationType;

};
