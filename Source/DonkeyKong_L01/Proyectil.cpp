// Fill out your copyright notice in the Description page of Project Settings.


#include "Proyectil.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProyectil::AProyectil()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Proyectil(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	ProyectilMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Proyectil"));
	ProyectilMesh->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
	ProyectilMesh->SetStaticMesh(Proyectil.Object);
	ProyectilMesh->OnComponentHit.AddDynamic(this, &AProyectil::OnHit);
	SetRootComponent(ProyectilMesh);


	ProyectilMovement = CreateDefaultSubobject<UProyectilMovementComponent>(TEXT("Movement_Proyectil"));
	ProyectilMovement->UpdatedComponent = ProyectilMesh;
	ProyectilMovement->InitialSpeed = 2500.f;
	ProyectilMovement->MaxSpeed = 2500.f;
	ProyectilMovement->bRotationFollowsVelocity = true;
	ProyectilMovement->bShouldBounce = false;
	ProyectilMovement->ProyectilGravityScale = 0.f;

	InitialLifeSpan = 2.f;
}


// Called when the game starts or when spawned
void AProyectil::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProyectil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AProyectil::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}

	Destroy();
}


