// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong_L01GameMode.h"
#include "DonkeyKong_L01Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Obstaculo.h"
#include "DonkeyKong_L01Character.h"
#include "ComponentePlataforma.h"
#include "Barril.h"

ADonkeyKong_L01GameMode::ADonkeyKong_L01GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	obstaculo01 = nullptr;
	player01 = nullptr;
	numeroBarriles = 0;

	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		player01 = Cast<ADonkeyKong_L01Character>(PlayerPawnBPClass.Class);
     
	}
}

void ADonkeyKong_L01GameMode::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, TEXT("Actor Spawning"));
	// Spawn an instance of the AMyFirstActor class at the
	//default location.
	FTransform SpawnLocation;
	SpawnLocation.SetLocation(FVector(1160.0f, -210.0f, 140.0f));
	SpawnLocation.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f)));
	obstaculo01 = GetWorld()->SpawnActor<AObstaculo>(AObstaculo::StaticClass(), SpawnLocation);
	if (player01 != nullptr)
	{
		player01->SetObstaculo(obstaculo01);
	}

	FVector posicionInicial = FVector(1160.0f, -1100.0f, 400.f);
	FRotator rotacionInicial = FRotator(0.0f, 0.0f, 10.0f);
	FTransform SpawnLocationCP;
	float anchoComponentePlataforma = 600.0f;
	float incrementoAltoComponentePlataforma = -105.0f;
	float incrementoAltoEntrePisos = 800.0f;
	float incrementoInicioPiso = 100.0f;
	int Componenteseparado1 ;
	int Componenteseparado2;
	float separacion = 0.0f;

	for (int npp = 0; npp < 5; npp++) {

		rotacionInicial.Roll = rotacionInicial.Roll * -1;
		incrementoInicioPiso = incrementoInicioPiso * -1;
		incrementoAltoComponentePlataforma = incrementoAltoComponentePlataforma * -1;
		SpawnLocationCP.SetRotation(FQuat(rotacionInicial));

		for (int ncp = 0; ncp < 8; ncp++) {
			if (ncp = Componenteseparado1 || ncp == Componenteseparado2) {
				separacion = 300.0f;
				if (npp % 2 == 0) {
					Componenteseparado1 -= 600.0f; // Mover a la derecha
				}
				else {
					Componenteseparado2 += 600.0f; // Mover a la izquierda
				}
			}
			SpawnLocationCP.SetLocation(FVector(posicionInicial.X, posicionInicial.Y + anchoComponentePlataforma * ncp, posicionInicial.Z));
			componentesPlataforma.Add(GetWorld()->SpawnActor<AComponentePlataforma>(AComponentePlataforma::StaticClass(), SpawnLocationCP));
			if (ncp < 7) {
				posicionInicial.Z = posicionInicial.Z + incrementoAltoComponentePlataforma;
			}
		}

		posicionInicial.Z = posicionInicial.Z + incrementoAltoEntrePisos;
		posicionInicial.Y = posicionInicial.Y + incrementoInicioPiso;
	}

	//SpawnBarril();
	GetWorldTimerManager().SetTimer(SpawnBarrilTimerHandle, this, &ADonkeyKong_L01GameMode::SpawnBarril, 5.0f, true);
	//SpawnLocation.SetLocation(FVector(1160.0f, 550.0f, 800.0f));
	//SpawnLocation.SetRotation(FQuat(FRotator(90.0f, 0.0f, 0.0f)));
	//barril01 = GetWorld()->SpawnActor<ABarril>(ABarril::StaticClass(), SpawnLocation);


}



void ADonkeyKong_L01GameMode::SpawnBarril()
{
	if (numeroBarriles < 5) {

		// Definir la ubicación y rotación para el nuevo barril
		FVector SpawnLocation = FVector(1160.0f, 550.0f, 800.0f); // Ajusta según sea necesario
		FRotator SpawnRotation = FRotator(90.0f, 0.0f, 0.0f);

		// Crear el actor barril
		barriles.Add(GetWorld()->SpawnActor<ABarril>(ABarril::StaticClass(), SpawnLocation, SpawnRotation));
		numeroBarriles++;
	}
}