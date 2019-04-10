// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"
#include "PlayerDwarf.generated.h"

UCLASS()
class GLADIATORGAME_API APlayerDwarf : public ACharacter
{
	GENERATED_BODY()
	
protected:

	FTimerHandle TimerHandle;
	FTimerHandle TimerAttackHandle;
	 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapons, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* Hammer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapons, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* Shield;
			
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterContent, meta = (AllowPrivateAccess = "true"))
		float m_health = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterContent, meta = (AllowPrivateAccess = "true"))
		float m_maxHealth = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterContent, meta = (AllowPrivateAccess = "true"))
		float m_damageDealtbyAttack = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapons, meta = (AllowPrivateAccess = "true"))
		bool HasWeapon = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapons, meta = (AllowPrivateAccess = "true"))
		bool m_isAttacking = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterContent")
		bool isAlive = true;


	bool m_CandealDamage = false;
	bool m_AttackInput = false;

	UFUNCTION(BlueprintCallable, Category = "AnimationNotify")
	void StopAttack();

	UFUNCTION(BlueprintCallable, Category = "AnimationNotify")
		void StartCanAttack();
	
	UFUNCTION(BlueprintCallable, Category = "AnimationNotify")
		void EndCanAttack();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAnimationEventDelegate, bool, isAttacked);

	void AttackLeftClick();
	
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parry, meta = (AllowPrivateAccess = "true"))
	bool isParrying		= false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parry, meta = (AllowPrivateAccess = "true"))
	bool canParry	= true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parry, meta = (AllowPrivateAccess = "true"))
	bool parrySuccesful = false;

	APlayerDwarf();

	void InitMeshes();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	void MoveForward(float p_value);
	void MoveRight(float p_value);
	void LookUpAtRate(float p_rate);
	void TurnAtRate(float p_rate);

	void Parry();

	void Die();

	FRotator GetYawRotation();

	UFUNCTION(BlueprintCallable, Category = "CharacterContent")
		void TakeDamages(const float p_damageTaken);

	UFUNCTION(BlueprintNativeEvent, Category = "CharacterContent")
	void OnTakeDamage(bool isAttacked);
	void OnTakeDamage_Implementation(bool isAttacked);

	UFUNCTION(BlueprintCallable, Category = "CharacterContent")
	bool DealDamages(AActor* ActorCollapsed);
	
	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FAnimationEventDelegate TakeDamageAnimationEvent;

	void OnTimeDone();

	bool	GetIsAlive();
	float	GetHealth();
};
