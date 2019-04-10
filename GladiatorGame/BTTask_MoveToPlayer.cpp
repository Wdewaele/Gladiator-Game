// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_MoveToPlayer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyCharacter.h"
#include "EnemyAI.h"
#include "PlayerDwarf.h"

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAI* EnemyAIController = Cast<AEnemyAI>(OwnerComp.GetAIOwner());

	AActor* actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(GetSelectedBlackboardKey()));
	FVector targetpos;
	
	if (actor)
	{
		targetpos = actor->GetActorLocation();
	}
	else
	{
		targetpos = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(GetSelectedBlackboardKey());
	}

	auto result = EnemyAIController->MoveToLocation(targetpos, Spacing, true, true, true, false, 0, true);

	if (result == EPathFollowingRequestResult::RequestSuccessful)
	{
		return EBTNodeResult::Succeeded;
	}
	else if(result == EPathFollowingRequestResult::Failed)
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}


