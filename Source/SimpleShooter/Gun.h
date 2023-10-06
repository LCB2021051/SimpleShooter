// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* Impact;

	UPROPERTY(EditAnywhere)
	float MaxRange = 2000;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	bool GunTrace(FHitResult &Hit, FVector &ShotDirection);

	AController* GetOwnerController() const;
};
