// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_AmIAlive.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyCharacter.h"
#include "EnemyAI.h"

bool UBTDecorator_AmIAlive::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AEnemyCharacter* enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetCharacter());

	if (enemy)
	{
		
		return enemy->Alive;
	}
	else
	{
		return false;
	}
}


