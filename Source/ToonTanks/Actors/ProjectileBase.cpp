// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	//UE_LOG(LogTemp,Warning,TEXT("dfd"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;

	InitialLifeSpan = 3.f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this,&AProjectileBase::OnHit);
}


void AProjectileBase::OnHit(UPrimitiveComponent* HitComp,AActor* OtherActor,UPrimitiveComponent* OtherComp, FVector NormalImpulse,const FHitResult& Hit) 
{
	
	AActor* MyOwner = GetOwner();

	if( !MyOwner )
	{
		return;
	}

	if( OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UE_LOG(LogTemp,Warning,TEXT("dfs"));
		UGameplayStatics::ApplyDamage(OtherActor ,Damage, MyOwner->GetInstigatorController(),this,DamageType);
	}

	Destroy();
}

void AProjectileBase::LaunchProjectile(FVector Speed) 
{
	ProjectileMovement->SetVelocityInLocalSpace(Speed);
	ProjectileMovement->Activate();    //可以飞行了
}
