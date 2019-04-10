// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_BossPickLocation.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BossCharacter.h"
#include "BossAIController.h"
#include "PlayerDwarf.h"

EBTNodeResult::Type UBTTask_BossPickLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABossAIController* BossAIController = Cast<ABossAIController>(OwnerComp.GetAIOwner());

	//AActor* actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(GetSelectedBlackboardKey()));
	
	if (BossAIController)
	{

		float x = FMath::RandRange(BossAIController->GetCharacter()->GetActorLocation().X - 1000.0f, BossAIController->GetCharacter()->GetActorLocation().X + 1000.0f);
	    float y = FMath::RandRange(BossAIController->GetCharacter()->GetActorLocation().Y - 1000.0f, BossAIController->GetCharacter()->GetActorLocation().Y + 1000.0f);

		FVector targetpos = FVector(x, y, BossAIController->GetCharacter()->GetActorLocation().Z);

		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(BossAIController->TargetPositionKey, targetpos);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

