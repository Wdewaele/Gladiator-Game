#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimerManager.h"
#include "AIHive.h"
#include "GladiatorGameGameModeBase.generated.h"

UCLASS()
class GLADIATORGAME_API AGladiatorGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	
	FTimerHandle TimerHandler;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEndConditionEventDelegate, bool, HasWon);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterContent, meta = (AllowPrivateAccess = "true"))
	AAIHive* Hive;
	
	bool isEndGame = false;

public:
	virtual void Tick(float p_deltatime) override;
	virtual void BeginPlay() override;

	void OnTimeDone();

	UFUNCTION(BlueprintNativeEvent, Category = "EndGameContent")
	void PlayerWon(bool HasWon);
	void PlayerWon_Implementation(bool HasWon);

	UFUNCTION(BlueprintNativeEvent, Category = "EndGameContent")
	void PlayerDied(bool HasWon);
	void PlayerDied_Implementation(bool HasWon);

public:

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
		FEndConditionEventDelegate WinCondition;	
};
