// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WraithGameMode.h"
#include "KillEMAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MAIN_API AKillEMAllGameMode : public AWraithGameMode
{
	GENERATED_BODY()
	public:
    virtual void PawnKilled(APawn* PawnKilled) override;
	private:
	void EndGame(bool bIsPlayerWinner);
};
