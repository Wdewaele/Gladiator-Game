// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerDwarf.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Uobject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "EnemyCharacter.h"
#include "BossCharacter.h"
#include "Components/SphereComponent.h"


APlayerDwarf::APlayerDwarf()
{
	PrimaryActorTick.bCanEverTick						= true;
	isAlive												= true;
	bUseControllerRotationPitch							= false;
	bUseControllerRotationYaw							= false;
	bUseControllerRotationRoll							= false;
	BaseTurnRate										= 45.f;
	BaseLookUpRate										= 45.f;

	GetCharacterMovement()->bOrientRotationToMovement	= true;  	
	GetCharacterMovement()->RotationRate				= FRotator(0.0f, 540.0f, 0.0f);

	CameraBoom											= CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength							= 300.0f; 	
	CameraBoom->bUsePawnControlRotation					= true;
												
	FollowCamera										= CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation				= false; 

	InitMeshes();
}

void APlayerDwarf::InitMeshes()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> obj(TEXT("SkeletalMesh'/Game/Characters/DwarfGrunt/SkelMesh/DwarfGrunt_R_new.DwarfGrunt_R_new'"));
	GetMesh()->SetSkeletalMesh(obj.Object);

	Hammer	= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hammer"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> HammerMesh(TEXT("SkeletalMesh'/Game/Characters/DwarfGrunt/SkelMesh/WarHammer.WarHammer'"));
	Hammer->SetSkeletalMesh(HammerMesh.Object);
	Hammer->SetupAttachment(GetMesh());

	Shield	= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Shield"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ShieldMesh(TEXT("SkeletalMesh'/Game/Characters/DwarfGrunt/SkelMesh/Shield_Skel.Shield_Skel'"));
	Shield->SetSkeletalMesh(ShieldMesh.Object);
	Shield->SetupAttachment(GetMesh());
}

void APlayerDwarf::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerDwarf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

void APlayerDwarf::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerDwarf::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerDwarf::MoveRight);
	
	PlayerInputComponent->BindAxis("TurnAtRate", this, &APlayerDwarf::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpAtRate", this, &APlayerDwarf::LookUpAtRate);

	PlayerInputComponent->BindAction("AttackLeftClick", IE_Pressed,this, &APlayerDwarf::AttackLeftClick);
	PlayerInputComponent->BindAction("Parry", IE_Pressed, this, &APlayerDwarf::Parry);

}

void APlayerDwarf::OnConstruction(const FTransform& Transform)
{
	Hammer->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("WeaponPoint"));
	Shield->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("DualWeaponPoint"));
	m_health = m_maxHealth;
}

void APlayerDwarf::LookUpAtRate(float p_rate)
{
	AddControllerPitchInput(p_rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerDwarf::TurnAtRate(float p_rate)
{
	AddControllerYawInput(p_rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerDwarf::Parry()
{
	if (canParry)
	{

		canParry = false;
		isParrying	= true;

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlayerDwarf::OnTimeDone, 0.15f, false);
	}
}

void APlayerDwarf::OnTimeDone()
{}

FRotator APlayerDwarf::GetYawRotation()
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	return YawRotation;
}




void APlayerDwarf::MoveForward(float p_value)
{
	if (m_isAttacking) return;

	if ((Controller != NULL) && (p_value != 0.0f) && isAlive)
	{
		const FVector Direction = FRotationMatrix(GetYawRotation()).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, p_value);
	}
}

void APlayerDwarf::MoveRight(float p_value)
{
	if (m_isAttacking) return;

	if ((Controller != NULL) && (p_value != 0.0f) && isAlive)
	{
		const FVector Direction = FRotationMatrix(GetYawRotation()).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, p_value);
	}
}
void APlayerDwarf::EndCanAttack()
{
	m_CandealDamage = false;
}
void APlayerDwarf::AttackLeftClick()
{
	if(HasWeapon)
	{
		m_AttackInput = true;
		if(!m_isAttacking)
		{
			GetWorld()->GetTimerManager().SetTimer(TimerAttackHandle, this, &APlayerDwarf::StopAttack, 1.3f, false);
			m_isAttacking = true;
		}
	}
}

void APlayerDwarf::StopAttack()
{
	m_isAttacking = false;
}

void APlayerDwarf::StartCanAttack()
{
	m_CandealDamage = true;
}

void APlayerDwarf::TakeDamages(const float p_damageTaken)
{
	m_health = FMath::Max(0.0f, m_health - p_damageTaken);
	
	OnTakeDamage(true);
	if (m_health <= 0.0f)
		Die();
	
}

void APlayerDwarf::OnTakeDamage_Implementation(bool isAttacked)
{
	if (isAttacked)
		TakeDamageAnimationEvent.Broadcast(true);	
}

bool APlayerDwarf::DealDamages(AActor* ActorCollapsed)
{
	if (ActorCollapsed)
	{
		AEnemyCharacter* Enemycollapsed = Cast<AEnemyCharacter>(ActorCollapsed);
		if(Enemycollapsed && m_CandealDamage)
		{
			if(parrySuccesful)
				Enemycollapsed->TakeDamage(m_damageDealtbyAttack * 3.0f);
			else
				Enemycollapsed->TakeDamage(m_damageDealtbyAttack);

			m_isAttacking = false;
			m_CandealDamage = false;
			return true;
		}

		ABossCharacter* BossChar = Cast<ABossCharacter>(ActorCollapsed);
		if (BossChar && m_CandealDamage)
		{
			/*if (parrySuccesful)
				BossChar->TakeDamage(m_damageDealtbyAttack * 3.0f);
			else
				BossChar->TakeDamage(m_damageDealtbyAttack);*/

			m_isAttacking = false;
			m_CandealDamage = false;
			return true;
		}
		return false;
	}
	return false;
}

void APlayerDwarf::Die()
{
	isAlive = false;
	m_CandealDamage = false;
}

bool APlayerDwarf::GetIsAlive()
{
	return isAlive;
}

float APlayerDwarf::GetHealth()
{
	return m_health;
}




