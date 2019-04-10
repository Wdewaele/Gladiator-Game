// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIHive.generated.h"

UCLASS()
class GLADIATORGAME_API AAIHive : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*>			Enemies;
	TArray<class AEnemyAI*>	EnemiesReadytoAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Peacefulness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Debug = false;

	float lastTime;

	float currentTime;

public:	
	// Sets default values for this actor's properties
	AAIHive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetAI();

	void CheckForStates();
};
