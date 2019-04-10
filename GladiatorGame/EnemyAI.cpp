// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyCharacter.h"


AEnemyAI::AEnemyAI()
{
	BlackboardComp				= CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	BehaviorTreeComp			= CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
}

void AEnemyAI::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AEnemyCharacter* Character	= Cast<AEnemyCharacter>(InPawn);

	if (Character && Character->BotBehavior)
	{
		BlackboardComp->InitializeBlackboard(*Character->BotBehavior->BlackboardAsset);

		EnemyKeyID				= BlackboardComp->GetKeyID("Target");
		TargetPositionKey		= BlackboardComp->GetKeyID("TargetPos");
		AttackingKey			= BlackboardComp->GetKeyID("Attack");
		StateKey				= BlackboardComp->GetKeyID("State");

		BehaviorTreeComp->StartTree(*Character->BotBehavior);

		BlackboardComp->SetValue<UBlackboardKeyType_Enum>(StateKey, static_cast<UBlackboardKeyType_Enum::FDataType>(enemyState));
	}
}

void AEnemyAI::Attack()
{
	BlackboardComp->SetValue<UBlackboardKeyType_Bool>(AttackingKey, true);
}

