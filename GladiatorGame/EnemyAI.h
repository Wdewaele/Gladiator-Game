// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAI.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class NPCState : uint8 {
	Waiting		UMETA(DisplayName		= "Enemy is Waiting instructions"),
	InPosition	UMETA(DisplayName		= "Enemy is in position"),
	Attacking	UMETA(DisplayName		= "Enemy is Attacking"),
	OnItsWay	UMETA(DisplayName		= "Enemy is on its way")
};

UCLASS()
class GLADIATORGAME_API AEnemyAI : public AAIController
{
	GENERATED_BODY()

public:

	UPROPERTY(transient)
		class UBlackboardComponent* BlackboardComp;

	UPROPERTY(transient)
		class UBehaviorTreeComponent* BehaviorTreeComp;

	AEnemyAI();

	virtual void Possess(APawn* InPawn) override;
	//virtual void Tick(float DeltaTime) override;

	void Attack();

	uint8 EnemyKeyID;
	uint8 TargetPositionKey;
	uint8 AttackingKey;
	uint8 StateKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	NPCState enemyState = NPCState::Waiting;
};
