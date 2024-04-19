
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameFramework/Actor.h"
#include "DataAsset/DA_ActData.h"
#include "DRRActableInterface.generated.h"

DECLARE_DELEGATE_OneParam(FOnActFuncDelegate,AActor* Owner)
DECLARE_DELEGATE_RetVal_OneParam( bool, FOnActCheckConditionDelegate, AActor*)

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDRRActableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DRR_API IDRRActableInterface
{
	GENERATED_BODY()

public:
	virtual FOnActFuncDelegate GetBeginActFunc() = 0;
	virtual TArray<FOnActFuncDelegate> GetActFunc() = 0;
	virtual FOnActFuncDelegate GetEndActFunc() = 0;
	virtual class UDA_ActData* GetActData() = 0;
	virtual FOnActCheckConditionDelegate GetAchieveCondition() = 0;


};
