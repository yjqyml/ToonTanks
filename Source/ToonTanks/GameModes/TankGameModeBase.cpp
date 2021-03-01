// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::BeginPlay() 
{
    Super::BeginPlay();
    // Get references and game win/lose conditions.

    // Call HandleGameStart() to initialise the start countdown, turret activation, pawn check etc.
    HandleGameStart();
}


void ATankGameModeBase::ActorDied(AActor* DeadActor) 
{
    //  Check what type of Actor died. If Turret, tally. If Player -> go to lose condition.
    //UE_LOG(LogTemp,Warning,TEXT("died"));
    if( DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);
    }
    else if( APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
    {
        DestroyedTurret->HandleDestruction();

        if( --TargetTurrets == 0)
        {
            HandleGameOver(true);
        }
    }
}

void ATankGameModeBase::HandleGameStart() 
{
    //  Initialise the start countdown, turret activation, pawn check etc.
    TargetTurrets = GetTargetTurretCount();

    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this,0));
    //  Call Blueprint version GameStart();
    GameStart();
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    //  See if the player has destroyed all the turrets, show win result.
    //  else if turret destroyed player, show lose result.
    //  Call bluprint version GameOver(bool).
    GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetTargetTurretCount() 
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(),APawnTurret::StaticClass(),TurretActors);
    return TurretActors.Num();
}




