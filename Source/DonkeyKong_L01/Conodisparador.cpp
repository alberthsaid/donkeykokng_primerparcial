// Fill out your copyright notice in the Description page of Project Settings.


#include "Conodisparador.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Proyectil.h"


// Sets default values
AConodisparador::AConodisparador()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));
	Meshcono = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Meshcono->SetStaticMesh(MeshAsset.Object);
	RootComponent = Meshcono;



	Fire = FVector(0.f, 90.f, 0.f);
	FireRate = 0.5f;
	bCanFire = true;

	Movimiento = FVector(0.0f, 100.0f, 0.0f);
}

// Called when the game starts or when spawned
void AConodisparador::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AConodisparador::Desaparecer, 15.0f, false);
}

// Called every frame
void AConodisparador::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Movimiento 
	FVector NuevaPosicion = GetActorLocation() + Movimiento * DeltaTime;
	SetActorLocation(NuevaPosicion);
	

}

void AConodisparador::FireShot()
{
	if (bCanFire == true) {
		FVector DirectionRight = FVector(0.f, -1.f, 0.f);
		FVector DirectionLeft = FVector(0.f, 1.f, 0.f);
		const FRotator FireRotationRight = DirectionRight.Rotation();
		const FRotator FireRotationLeft = DirectionLeft.Rotation();
		const FVector SpawnLocationRight = GetActorLocation() + FireRotationRight.RotateVector(Fire);
		const FVector SpawnLocationLeft = GetActorLocation() + FireRotationLeft.RotateVector(Fire);
		UWorld* const World1 = GetWorld();
		if (World1 != nullptr) {
			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("Spawneo")));
			World1->SpawnActor<AProyectil>(SpawnLocationRight, FireRotationRight);
			World1->SpawnActor<AProyectil>(SpawnLocationLeft, FireRotationLeft);
		}
		bCanFire = false;
		World1->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AConodisparador::ShotTimer, FireRate);
	}

}

void AConodisparador::ShotTimer()
{

	bCanFire = true;

}

void AConodisparador::Desaparecer()
{

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AConodisparador::Reaparecer, 5.0f, false);
}

void AConodisparador::Reaparecer()
{
	FVector NuevaPosicion = FVector(1180.0f, FMath::RandRange(-1000.0f, 1000.0f), GetActorLocation().Z);
	SetActorLocation(NuevaPosicion);
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AConodisparador::Desaparecer, 15.0f, false);
}

