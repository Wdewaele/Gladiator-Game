// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Attack.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyCharacter.h"
#include "EnemyAI.h"



EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	m_OwnerComp = &OwnerComp;

	AEnemyCharacter* AICharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetCharacter());

	if (AICharacter)
	{
		AICharacter->Attack = true;

		
		AICharacter->GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBTTask_Attack::OnTimeDone, 1.0f, false); //black magic
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}

void UBTTask_Attack::OnTimeDone()
{
	TimerHandle.Invalidate();

	if (m_OwnerComp)
	{
		AEnemyAI* EnemyAIController = Cast<AEnemyAI>(m_OwnerComp->GetAIOwner());

		if (EnemyAIController)
			m_OwnerComp->GetBlackboardComponent()->SetValue<UBlackboardKeyType_Enum>(EnemyAIController->StateKey, static_cast<UBlackboardKeyType_Enum::FDataType>(NPCState::Waiting));

		FinishLatentTask(*m_OwnerComp, EBTNodeResult::Succeeded);
	}
}

