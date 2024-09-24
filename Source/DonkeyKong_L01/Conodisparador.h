// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Conodisparador.generated.h"

UCLASS()
class DONKEYKONG_L01_API AConodisparador : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConodisparador();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	class UStaticMeshComponent* Meshcono;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Fire;

	float FireRate;

	uint32 bCanFire : 1;

	void FireShot();

	FTimerHandle TimerHandle_ShotTimerExpired;
	void ShotTimer();

	//  para que se mueva 
	FVector Movimiento;
	FTimerHandle TimerHandle;
	void Desaparecer();
	void Reaparecer();

};
