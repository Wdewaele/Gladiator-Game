// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossAIController.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class BOSSSTATE : uint8 {
	Wait		UMETA(DisplayName = "Boss is Waiting instructions"),
	Ready		UMETA(DisplayName = "Boss is in position"),
	Attacking	UMETA(DisplayName = "Boss is Attacking"),
	OnItsWay	UMETA(DisplayName = "Boss is on its way"),
	Taunting	UMETA(DisplayName = "Boss is Taunting"),
	Avoiding	UMETA(DisplayName = "Boss is Avoiding the player")
};

UCLASS()
class GLADIATORGAME_API ABossAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(transient)
	class UBehaviorTreeComponent* BehaviorTreeComp;

	ABossAIController();

	virtual void Possess(APawn* InPawn) override;
	//virtual void Tick(float DeltaTime) override;

	void Attack();

	uint8 PlayerKey;
	uint8 TargetPositionKey;
	uint8 StateKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	BOSSSTATE currentState = BOSSSTATE::Wait;
	
	
};
