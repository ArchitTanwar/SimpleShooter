// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEMAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "WraithAIController.h"

void AKillEMAllGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);
    
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if(PlayerController != nullptr)
    {
      EndGame(false);
    }
    for(AWraithAIController* Controller : TActorRange<AWraithAIController>(GetWorld()))
    {
        if(!Controller->IsDead())
        {
            return;
        }
    }
    EndGame(true);

}
void AKillEMAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for(AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    } 
}

