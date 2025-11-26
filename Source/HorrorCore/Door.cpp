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
	UE_LOG(LogTemp, Warning, TEXT("ADoor::Interact called by %s"), *Interactor->GetName());

	if (!Interactor) return;

	bIsOpen = !bIsOpen;

	if (bIsOpen)
	{	
		FVector DoorForward = FrameMesh->GetForwardVector();
		FVector ToPlayer = Interactor->GetActorLocation() - GetActorLocation();
		ToPlayer.Normalize();

		float Dot = FVector::DotProduct(DoorForward, ToPlayer);

		if (Dot < 0)
		{
			TargetYaw = InitialYaw + OpenAngle;
		}
		
		else
		{
			TargetYaw = InitialYaw - OpenAngle;
		}

		//UE_LOG(LogTemp, Warning, TEXT("Door opened by %s"), *Interactor->GetName());
	}

	else
	{
		TargetYaw = InitialYaw;
		//UE_LOG(LogTemp, Warning, TEXT("Door closed by %s"), *Interactor->GetName());
	}

}