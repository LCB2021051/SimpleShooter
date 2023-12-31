// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAiController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterAiController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	bool IsDead() const;
	
	// UPROPERTY(EditAnywhere)
	// float AcceptanceRadius = 200;
private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;
};
