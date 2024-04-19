
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/DRRActableInterface.h"
#include "DRRAct.h"
#include "DataAsset/DA_ActData.h"
#include "DRRActComponent.generated.h"



//매개변수가 하나인 델리게이트 생성

//DECLARE_DELEGATE_OneParam(FOnActDelegate, class IDRRActableInterface* );

DECLARE_DELEGATE_RetVal_OneParam(class DRRAct*,FOnActDelegate, class IDRRActableInterface*)
DECLARE_DELEGATE(FOnDoActDelegate);
USTRUCT(BlueprintType)
struct FOnActDelegateWrapper
{
	GENERATED_BODY()

	FOnActDelegateWrapper() {}
	FOnActDelegateWrapper(const FOnActDelegate& InActDelegate) :ActDelegate(InActDelegate) {}

	FOnActDelegate ActDelegate;

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRR_API UDRRActComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDRRActComponent();

	void Act(class IDRRActableInterface* Actable); 
	void ActRelease(class IDRRActableInterface* Actable);

	
	void ActFunc();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void AfterAct();

	//UFUNCTION()
	class DRRAct* ShortShot(class IDRRActableInterface* Target);
	//UFUNCTION()
	class DRRAct* Charging(class IDRRActableInterface* Target);
	//UFUNCTION()
	class DRRAct* Casting(class IDRRActableInterface* Target);
	//UFUNCTION()
	class DRRAct* Combo(class IDRRActableInterface* Target);
	//UFUNCTION()
	class DRRAct* Trigger(class IDRRActableInterface* Target);


	void BeginAct();
	void CheckActTimer();
	void EndTimer();
	void CheckAct();
	void EndAct(UAnimMontage* targetMontage, bool isInteruped);
	void ClearMontageAct();


	virtual void BeginDestroy() override;
private:
	void EraseAct();
	
	void SetActor(IDRRActableInterface* Target);


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:



	UPROPERTY()
	TArray<FOnActDelegateWrapper> ActActions;

	DRRAct* PrevActor;

	DRRAct* Actor;

	TObjectPtr<class UAnimMontage> ActionMontage;


	struct FTimerHandle ActTimerHandle;
	struct FTimerHandle PrevActTimerHandle;
	bool hasNextAct;
	bool TryInput;

		
};

