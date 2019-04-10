// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "PlayerDwarf.h"
#include "Components/CapsuleComponent.h"
#include "EnemyAI.h"
#include "DrawDebugHelpers.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIHive.h"

#include "EngineUtils.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick	= true;

	Alive							= true;
	CanDealDamage					= false;
	MaxLife							= 3;
	LifePoints						= MaxLife;

}

void AEnemyCharacter::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		
	}
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AEnemyAI* aiController = Cast<AEnemyAI>(GetController());

	if (aiController)
	{
		UPathFollowingComponent* path = aiController->GetPathFollowingComponent();
		if (path)
		{
			FVector movedir = path->GetCurrentDirection();
			
			movedir = GetActorTransform().InverseTransformVectorNoScale(movedir);

			MoveDir = movedir;
		}
	}

	if (debug)
	{
		FVector Pos = GetActorLocation() + FVector(0, 0, 100.0f);
		DrawDebugSphere(GetWorld(), Pos, 10.0f, 8, FColor::Red, false, 0.0f);
	}

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyCharacter::StopAttack()
{
	Attack			= false;
}

void AEnemyCharacter::TakeDamage(const float DamageTaken)
{
	
	LifePoints = FMath::Max(0.0f, LifePoints - DamageTaken);

	if (LifePoints <= 0.0f)
		Die();

}

void AEnemyCharacter::DealDamage(AActor* Otheractor)
{

	if (Otheractor && CanDealDamage)
	{
		APlayerDwarf* player = Cast<APlayerDwarf>(Otheractor);

		if (player && CanDealDamage)
		{
			if (player->isParrying)
			{
				
				player->parrySuccesful	= true;
				player->isParrying		= false;

				CanDealDamage			= false;
				Attack					= false;
				return;
			}
			player->TakeDamages(AttackPoints);
			
			CanDealDamage				= false;
			Attack						= false;
		}
	}

}

void AEnemyCharacter::Die()
{
	Alive			= false;
	CanDealDamage	= false;
	Attack			= false;

	AEnemyAI* AI	= Cast<AEnemyAI>(GetController());
	if (AI)
	{
		AI->SetActorTickEnabled(false);
	}

	this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->GetCapsuleComponent()->bDynamicObstacle = false;

	debug = false;
}

void AEnemyCharacter::ShowDebug(bool visible)
{
	debug = visible;
}

