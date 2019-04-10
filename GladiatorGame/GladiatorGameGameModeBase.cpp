// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGameGameModeBase.h"
#include "PlayerDwarf.h"
#include "EngineUtils.h"
#include "UObject/UObjectIterator.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

void AGladiatorGameGameModeBase::Tick(float p_deltatime)
{
	TimerHandler.Invalidate();

	 APlayerDwarf*			player = Cast<APlayerDwarf>(UGameplayStatics::GetPlayerCharacter(this, 0));
	 if (player)
	 {
		 if(player->GetHealth() <= 0)
		 {
			 isEndGame = true;
			 PlayerDied(player->GetIsAlive());
			 player->GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &AGladiatorGameGameModeBase::OnTimeDone, 5.0f, false);	 
		 }
		 else if (Hive && Hive->Enemies.Num() <= 0)
		 {
			 isEndGame = true;
			 PlayerWon(player->GetIsAlive());
			 player->GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &AGladiatorGameGameModeBase::OnTimeDone, 5.0f, false);
		 }
	 }
}

void AGladiatorGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	for(TObjectIterator<AAIHive> it; it; ++it)
	{
		Hive = *it;
	}
}

void AGladiatorGameGameModeBase::OnTimeDone()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AGladiatorGameGameModeBase::PlayerWon_Implementation(bool HasWon)
{
	if (HasWon)
		WinCondition.Broadcast(true);
}

void AGladiatorGameGameModeBase::PlayerDied_Implementation(bool HasWon)
{
	if (!HasWon)
		WinCondition.Broadcast(false);
}


