// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle,this,&APawnTurret::CheckFireCondition,FireRate,true);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this,0));

    Test();
}

void APawnTurret::HandleDestruction() 
{
    // Call base pawn class HandleDestruction to play effects.
    Super::HandleDestruction();
    Destroy();
}

void APawnTurret::Test() 
{
    Super::Test();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if( !PlayerPawn || ReturnDistanceToPlayer() > FireRange)
    {
        return;
    }

    RotateTurretFunction(PlayerPawn->GetActorLocation());
}
void APawnTurret::CheckFireCondition() 
{
    // If Player == null || is Dead THEN BAIL
    if( !PlayerPawn)
    {
        return;
    }
    // If Player IS in Range THEN FIRE
    if( ReturnDistanceToPlayer() <= FireRange)
    {
        //Fire
        Fire();
    }

}

float APawnTurret::ReturnDistanceToPlayer() 
{
    if( !PlayerPawn)
    {
        return 0.f;
    }

    return FVector::Dist(PlayerPawn->GetActorLocation(),GetActorLocation());
}
