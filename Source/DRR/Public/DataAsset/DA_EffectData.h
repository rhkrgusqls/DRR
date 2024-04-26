
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_EffectData.generated.h"



//상시, 공격시, 타격시, 피격시
UENUM()
enum class EPassiveType : uint8
{
	Auto=0,
	Attack,
	Damage,
	Hit
};

//효과의 만료 타입. 시간, 사용횟수, 영구
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

	//update의 간격
	UPROPERTY(EditAnywhere, Category = Section)
	float PassiveDelay;

	//지속시간
	UPROPERTY(EditAnywhere, Category = Section)
	float PassiveDuration;

	//사용가능 횟수
	UPROPERTY(EditAnywhere, Category = Section)
	uint8 UsageCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	EPassiveType UseType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	EExpirationType ExpirationType;

};
