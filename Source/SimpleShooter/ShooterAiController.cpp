// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAiController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAiController::BeginPlay()
{
    Super::BeginPlay();

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    
    if(AIBehavior != nullptr){
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }


}

void AShooterAiController::Tick(float DeltaTime)
{   
    Super::Tick(DeltaTime);
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    
    //If line of site 
    if(LineOfSightTo(PlayerPawn)){
        //setting playerLocation & PlayerLastKnownLoation
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());



    }
    else{
        //clear PlayerLocation
        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    } 
}