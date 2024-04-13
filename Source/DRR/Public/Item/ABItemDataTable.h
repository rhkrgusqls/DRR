// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ABItemDataTable.generated.h"

USTRUCT(BlueprintType)
struct FItem : public FTableRowBase {
	GENERATED_BODY()

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString ItemName;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float ATK;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float DEF;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Range;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Speed;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float HP;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float MP;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Heal;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString	Type;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString	Description;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		bool Countable;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		USkeletalMesh* Mesh;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		UTexture* Img;

		
};

UCLASS()
class DRR_API AABItemDataTable : public AActor
{
	GENERATED_BODY()

public:	
	static AABItemDataTable* m_staticInstance;
	// Sets default values for this actor's properties
	AABItemDataTable();


};
