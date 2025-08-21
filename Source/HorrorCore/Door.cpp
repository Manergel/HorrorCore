#include "Door.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetActorRotation().Yaw;
	TargetYaw = InitialYaw;

}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CurrentRotation = GetActorRotation();
	float NewYaw = FMath::FInterpConstantTo(CurrentRotation.Yaw, TargetYaw, DeltaTime, OpenSpeed);
	SetActorRotation(FRotator(CurrentRotation.Pitch, NewYaw, CurrentRotation.Roll));

}


void ADoor::Interact(AActor* Interactor)
{
	bIsOpen = !bIsOpen;

	if (bIsOpen)
	{
		TargetYaw = InitialYaw + OpenAngle;
		UE_LOG(LogTemp, Warning, TEXT("Door opened by %s"), *Interactor->GetName());
	}

	else
	{
		TargetYaw = InitialYaw;
		UE_LOG(LogTemp, Warning, TEXT("Door closed by %s"), *Interactor->GetName());
	}

}








