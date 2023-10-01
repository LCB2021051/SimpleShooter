// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_Socket"));
	Gun->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//binding of input to the pawn
	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUP"),this,&APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this,&AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"),this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"),this,&AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"),this,&AShooterCharacter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"),EInputEvent::IE_Pressed,this,&AShooterCharacter::Shoot);

}

void AShooterCharacter::MoveForward(float AxixValue)
{
	AddMovementInput(GetActorForwardVector()*AxixValue);
}

void AShooterCharacter::MoveRight(float AxixValue)
{
	AddMovementInput(GetActorRightVector()*AxixValue);
}

void AShooterCharacter::LookUpRate(float AxixValue)
{
	//gamepad look up-down movements
	AddControllerPitchInput(AxixValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate( float AxixValue)
{
	//gamepad look right-left movements
	AddControllerYawInput(AxixValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}

