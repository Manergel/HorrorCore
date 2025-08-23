#include "Door.h"


ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	RootComponent = FrameMesh;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(FrameMesh);
	DoorMesh->SetRelativeLocation(FVector::ZeroVector);
	DoorMesh->SetRelativeRotation(FRotator::ZeroRotator);
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

	FRotator CurrentRotation = DoorMesh->GetRelativeRotation();
	float NewYaw = FMath::FInterpConstantTo(CurrentRotation.Yaw, TargetYaw, DeltaTime, OpenSpeed);
	DoorMesh->SetRelativeRotation(FRotator(CurrentRotation.Pitch, NewYaw, CurrentRotation.Roll));

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









