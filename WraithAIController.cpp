// Fill out your copyright notice in the Description page of Project Settings.


#include "WraithAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Wraith.h"

void AWraithAIController::BeginPlay()
{
    Super::BeginPlay(); 

    if(AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        
      
        GetBlackboardComponent() -> SetValueAsVector(TEXT("StartLocation"), GetPawn() -> GetActorLocation());
    }
}
void AWraithAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
bool AWraithAIController::IsDead() const
{
    AWraith* ControlledCharacter = Cast<AWraith>(GetPawn());
    if(ControlledCharacter != nullptr)
    {
        return ControlledCharacter -> IsDead();
    }
    return true;
}
