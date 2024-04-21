// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/AIController/BTActionTask/BTSObserverLeaderPatrol.h"

UBTSObserverLeaderPatrol::UBTSObserverLeaderPatrol()
{
}

void UBTSObserverLeaderPatrol::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{/*
	AAIController* Controller = Cast<AAIController>(OwnerComp.GetAIOwner());
	if (Controller)
	{
		//bool IsPlayerCast = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("IsCasstPlayer"));
		//if (IsPlayerCast)
		//{
			//Controller->StopAI();
			//Controller->RestartAI();
		//}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CastFaile"));
	}*/
}
