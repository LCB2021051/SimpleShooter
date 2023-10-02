// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAiController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAiController::BeginPlay()
{
    Super::BeginPlay();
    APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    SetFocus(Player);
}

void AShooterAiController::Tick(float DeltaTime)
{   
    Super::Tick(DeltaTime);
    APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    SetFocus(Player);
    MoveToActor(Player, 200);
}