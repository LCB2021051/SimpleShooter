// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameModeBase.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAiController.h"

void AKillEmAllGameModeBase::PawnKilled(APawn *PawnKilled)
{
    Super::PawnKilled(PawnKilled);
    // UE_LOG(LogTemp, Warning, TEXT("Pawn was killed"));
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if(PlayerController != nullptr){
        // PlayerController->GameHasEnded(nullptr,false);
        EndGame(false);
    }

    //for loop over ShooterAI in World;
    for(AShooterAiController* Controller : TActorRange<AShooterAiController>(GetWorld())){
        //If any one of them is alive then game has not ended
        if(!Controller->IsDead()){
            return;
        }
    }
    EndGame(true);
}

void AKillEmAllGameModeBase::EndGame(bool bIsPlayerWinner)
{
    for(AController* Controller : TActorRange<AController>(GetWorld())){
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(),bIsWinner);
    }
}
