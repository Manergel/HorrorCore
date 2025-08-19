#include "Door.h"

ADoor::ADoor()
{

	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;

}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentAlpha = FMath::FInterpTo(CurrentAlpha, TargetAlpha, DeltaTime, OpenSpeed);

	float CurrentYaw = FMath::Lerp(0.0f, OpenAngle, CurrentAlpha);
	DoorMesh->SetRelativeRotation(FRotator(0, CurrentYaw, 0));

}

void ADoor::Interact(class AActor*)
{
	if (bIsOpen)
	{
		TargetAlpha = 0.0f;
		bIsOpen = false;
	}
	
	else
	{
		TargetAlpha = 1.0f;
		bIsOpen = true;
	}
}







