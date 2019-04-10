// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_BossAIPlayerCheck.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API UBTService_BossAIPlayerCheck : public UBTService
{
	GENERATED_BODY()
public:

	UBTService_BossAIPlayerCheck();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
};
