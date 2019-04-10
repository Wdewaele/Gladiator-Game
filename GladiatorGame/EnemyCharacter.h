// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class GLADIATORGAME_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	//Variables
public:

	UPROPERTY(EditAnywhere, Category = "Behavior")
	class UBehaviorTree* BotBehavior; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Behavior")
	bool Alive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
	bool CanDealDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
	bool Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
	float MaxLife;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
	float LifePoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
	FVector MoveDir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
	float AttackPoints = 1.0f;

	bool debug = false;

	//Methods
public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	void OnDeathEvent();

	void TakeDamage(const float damageTaken);

	void Die();

	void ShowDebug(bool visible);

	UFUNCTION(BlueprintCallable, Category = "AIContent")
	void StopAttack();

	UFUNCTION(BlueprintCallable, Category = "AIContent")
	void DealDamage(AActor* Otheractor);

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
