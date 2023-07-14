// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WraithGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MAIN_API AWraithGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
    virtual void PawnKilled(APawn* PawnKilled);
	
};
