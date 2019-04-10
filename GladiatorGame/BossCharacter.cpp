// Fill out your copyright notice in the Description page of Project Settings.

#include "BossCharacter.h"
#include "PlayerDwarf.h"
#include "Components/CapsuleComponent.h"
#include "BossAIController.h"
#include "DrawDebugHelpers.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

#include "EngineUtils.h"


// Sets default values
ABossCharacter::ABossCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Alive			= true;
	CanDealDamage	= false;
	MaxLife			= 10;
	LifePoints		= MaxLife;

}

// Called when the game starts or when spawned
void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ABossAIController* aiController = Cast<ABossAIController>(GetController());

	if (aiController)
	{
		UBlackboardComponent* BBComp = aiController->GetBlackboardComponent();
		if (BBComp)
		{
			BBComp->SetValue<UBlackboardKeyType_Enum>(aiController->StateKey, static_cast<UBlackboardKeyType_Enum::FDataType>(aiController->currentState));
		}

		UPathFollowingComponent* path = aiController->GetPathFollowingComponent();
		if (path)
		{
			FVector movedir = path->GetCurrentDirection();

			movedir = GetActorTransform().InverseTransformVectorNoScale(movedir);

			MoveDir = movedir;
		}
	}

}

// Called to bind functionality to input
void ABossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

