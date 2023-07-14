// Fill out your copyright notice in the Description page of Project Settings.


#include "Wraith.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "WraithGameMode.h"

// Sets default values
AWraith::AWraith()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWraith::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	Gun = GetWorld() -> SpawnActor<AGun>(GunClass);
	GetMesh() -> HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun -> AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun -> SetOwner(this);
	
}

// Called every frame
void AWraith::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWraith::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent -> BindAxis(TEXT("MoveForward"),this, &AWraith::MoveForward);
	PlayerInputComponent -> BindAxis(TEXT("MoveRight"),this, &AWraith::MoveRight);
	PlayerInputComponent -> BindAxis(TEXT("LookUp"),this, &APawn::AddControllerPitchInput);
	PlayerInputComponent -> BindAxis(TEXT("LookRight"),this, &APawn::AddControllerYawInput);
	PlayerInputComponent -> BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AWraith::Jump);
	PlayerInputComponent -> BindAxis(TEXT("LookUpRate"),this, &AWraith::LookUpRate);
	PlayerInputComponent -> BindAxis(TEXT("LookRightRate"),this, &AWraith::LookRightRate); 
	PlayerInputComponent -> BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AWraith::Shoot);

}

void AWraith::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}
void AWraith::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}
void AWraith::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld() -> GetDeltaSeconds());
}
void AWraith::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld() -> GetDeltaSeconds());
}
void AWraith::Shoot()
{
	Gun -> PullTrigger();
}
float AWraith::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamagetoApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamagetoApply = FMath::Min(Health, DamagetoApply);
	Health -= DamagetoApply;
	UE_LOG(LogTemp, Warning, TEXT("Health is %f"), Health);

	if(IsDead())
	{
		AWraithGameMode* GameMode = GetWorld()->GetAuthGameMode<AWraithGameMode>();
		 if(GameMode != nullptr)
		{
			GameMode -> PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	   
	}
	return DamagetoApply;
}
float AWraith::GetHealthPercent() const
{
    return Health/MaxHealth;
}
bool AWraith::IsDead() const
{
	return Health <= 0;
}
