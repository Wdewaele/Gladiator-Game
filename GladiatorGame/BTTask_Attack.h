// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "TimerManager.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API UBTTask_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBehaviorTreeComponent* m_OwnerComp;

	FTimerHandle TimerHandle;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void OnTimeDone();
	
};
