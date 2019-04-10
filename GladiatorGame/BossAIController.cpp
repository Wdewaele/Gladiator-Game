// Fill out your copyright notice in the Description page of Project Settings.

#include "BossAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BossCharacter.h"

ABossAIController::ABossAIController()
{
	Blackboard			= CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	BehaviorTreeComp	= CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
}

void ABossAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	ABossCharacter* Character = Cast<ABossCharacter>(InPawn);

	if (Character && Character->AI)
	{
		Blackboard->InitializeBlackboard(*Character->AI->BlackboardAsset);

		BehaviorTreeComp->StartTree(*Character->AI);

		PlayerKey			= Blackboard->GetKeyID("Player");
		TargetPositionKey	= Blackboard->GetKeyID("Target");
		StateKey			= Blackboard->GetKeyID("State");

		Blackboard->SetValue<UBlackboardKeyType_Enum>(StateKey, static_cast<UBlackboardKeyType_Enum::FDataType>(currentState));
	}

}