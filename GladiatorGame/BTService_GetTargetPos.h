// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_GetTargetPos.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API UBTService_GetTargetPos : public UBTService
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float MaxDistance = 400.0f;


public:

	UBTService_GetTargetPos();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	void ChangeState(class AEnemyAI* enemy, uint8 state);
	
};
