// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_GetTargetPos.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyCharacter.h"
#include "EnemyAI.h"
#include "PlayerDwarf.h"


UBTService_GetTargetPos::UBTService_GetTargetPos()
{
	bCreateNodeInstance = true;
}

void UBTService_GetTargetPos::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AEnemyAI* EnemyAIController = Cast<AEnemyAI>(OwnerComp.GetAIOwner());

	if (EnemyAIController)
	{
		APlayerDwarf* Player = Cast<APlayerDwarf>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyAIController->EnemyKeyID));

		if (Player && EnemyAIController->GetCharacter())
		{
			float distance = FVector::Distance(Player->GetActorLocation(), EnemyAIController->GetCharacter()->GetActorLocation());
			
			if (distance > MaxDistance)
			{
				EnemyAIController->ClearFocus(EAIFocusPriority::Gameplay);

				FVector TargetPos = Player->GetActorLocation();
				
				OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(EnemyAIController->TargetPositionKey, TargetPos);
				ChangeState(EnemyAIController, static_cast<UBlackboardKeyType_Enum::FDataType>(NPCState::OnItsWay));
			}
			else if(distance <= MaxDistance)
			{

				EnemyAIController->SetFocus(Player);

				FVector Dir = EnemyAIController->GetCharacter()->GetActorLocation() - Player->GetActorLocation();

				Dir.Normalize();

				Dir *= MaxDistance;

				FVector TargetPos = Player->GetActorLocation() + Dir;

				OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(EnemyAIController->TargetPositionKey, TargetPos);
				ChangeState(EnemyAIController, static_cast<UBlackboardKeyType_Enum::FDataType>(NPCState::InPosition));
			}
		}
	}
}

void UBTService_GetTargetPos::ChangeState(AEnemyAI* enemy, uint8 state)
{
	NPCState	newState		= static_cast<NPCState>(state);
	uint8		stateGot		= static_cast<uint8>(enemy->BehaviorTreeComp->GetBlackboardComponent()->GetValue<UBlackboardKeyType_Enum>(enemy->StateKey));
	NPCState	prevState		= static_cast<NPCState>(stateGot);

	if (prevState != newState && prevState != NPCState::Attacking)
	{
		enemy->BehaviorTreeComp->GetBlackboardComponent()->SetValue<UBlackboardKeyType_Enum>(enemy->StateKey, static_cast<UBlackboardKeyType_Enum::FDataType>(newState));
	}
}