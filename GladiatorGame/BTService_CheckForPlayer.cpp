// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_CheckForPlayer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyCharacter.h"
#include "EnemyAI.h"
#include "PlayerDwarf.h"


UBTService_CheckForPlayer::UBTService_CheckForPlayer()
{
	bCreateNodeInstance		= true;
}

void UBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	AEnemyAI* EnemyAIController = Cast<AEnemyAI>(OwnerComp.GetAIOwner());

	if (EnemyAIController)
	{
		APlayerDwarf* Player = Cast<APlayerDwarf>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (Player && Player->GetIsAlive())
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyAIController->EnemyKeyID, Player);
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->ClearValue(EnemyAIController->EnemyKeyID);
		}
	}
}

