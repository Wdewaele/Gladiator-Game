// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_BossAIPlayerCheck.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BossCharacter.h"
#include "BossAIController.h"
#include "PlayerDwarf.h"


UBTService_BossAIPlayerCheck::UBTService_BossAIPlayerCheck()
{
	bCreateNodeInstance = true;
}

void UBTService_BossAIPlayerCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ABossAIController* BossAIController = Cast<ABossAIController>(OwnerComp.GetAIOwner());

	if (BossAIController)
	{
		APlayerDwarf* Player = Cast<APlayerDwarf>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (Player && Player->GetIsAlive())
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(BossAIController->PlayerKey, Player);
			//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Enemy is here")); //Comments in unreal
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->ClearValue(BossAIController->PlayerKey);
		}
	}
}
