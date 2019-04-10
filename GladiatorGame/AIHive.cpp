// Fill out your copyright notice in the Description page of Project Settings.

#include "AIHive.h"
#include "Kismet/GameplayStatics.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

#include "EnemyAI.h"
#include "EnemyCharacter.h"

#include "TimerManager.h"


// Sets default values
AAIHive::AAIHive()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//TimerDel = FTimerDelegate::bi
}

// Called when the game starts or when spawned
void AAIHive::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyAI::StaticClass(), Enemies);

	lastTime = currentTime + Peacefulness;

	
}

// Called every frame
void AAIHive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;

	if (currentTime > lastTime)
	{
		CheckForStates();
		SetAI();
		lastTime = currentTime + Peacefulness;
	}
}

	

void AAIHive::SetAI()
{
	
	if (EnemiesReadytoAttack.Num() > 0)
	{		

		float rand		= FMath::RandRange(0, EnemiesReadytoAttack.Num() - 1);
		AEnemyAI* e		= EnemiesReadytoAttack[rand];

		if (e)
		{
			if (Debug)
			{
				AEnemyCharacter* c = Cast<AEnemyCharacter>(e->GetCharacter());
				
				if (c)
				{
					c->ShowDebug(Debug);
				}
			}
			e->BehaviorTreeComp->GetBlackboardComponent()->SetValue<UBlackboardKeyType_Enum>(e->StateKey, static_cast<UBlackboardKeyType_Enum::FDataType>(NPCState::Attacking));
		}
	}
}

void AAIHive::CheckForStates()
{
	AActor* toRemove = NULL;

	for (AActor* a : Enemies)
	{
		AEnemyAI* e = Cast<AEnemyAI>(a);

		if (e)
		{
			AEnemyCharacter*	c		= Cast<AEnemyCharacter>(e->GetCharacter());
			uint8				n		= static_cast<uint8>(e->BehaviorTreeComp->GetBlackboardComponent()->GetValue<UBlackboardKeyType_Enum>(e->StateKey));
			NPCState			state	= static_cast<NPCState>(n);

			if (c)
			{
				if (state == NPCState::InPosition && c->Alive)
				{
					if (!EnemiesReadytoAttack.Contains(e))
						EnemiesReadytoAttack.Add(e);
				}
				else
				{
					if (EnemiesReadytoAttack.Contains(e))
						EnemiesReadytoAttack.Remove(e);
				}
				c->ShowDebug(false);

				if (!c->Alive)
				{
					if (EnemiesReadytoAttack.Contains(e))
						EnemiesReadytoAttack.Remove(e);

					toRemove = a;
				}
			}
			else
			{
				if (EnemiesReadytoAttack.Contains(e))
					EnemiesReadytoAttack.Remove(e);
			}
		}
	}

	if (toRemove)
	{
		if (Enemies.Contains(toRemove))
			Enemies.Remove(toRemove);
	}
}
