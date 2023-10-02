// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root); 

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	
}

void AGun::PullTrigger()
{
	// UE_LOG(LogTemp, Warning, TEXT("You've Been Shot!"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;
	
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;

	OwnerController->GetPlayerViewPoint(Location,Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;

	FHitResult HitResult;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, Location, End, ECollisionChannel::ECC_GameTraceChannel1);
	
	// DrawDebugCamera(GetWorld(), Location, Rotation, 90, 1, FColor::Red, true);
	if(bSuccess){
		// DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Green, true);
		FVector ShotDirection = -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Impact, HitResult.Location, ShotDirection.Rotation(), true);
		AActor* HitActor = HitResult.GetActor();
		
		if(HitActor!=nullptr) {
			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

