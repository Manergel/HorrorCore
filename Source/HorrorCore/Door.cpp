#include "Door.h"
#include "MyCharacter.h"


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

	DoorMesh->GetRelativeRotation();
	TargetYaw = InitialYaw;
	
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMoving)
	{
		FRotator CurrentRotation = DoorMesh->GetRelativeRotation();
		float NewYaw = FMath::FInterpConstantTo(CurrentRotation.Yaw, TargetYaw, DeltaTime, OpenSpeed);
		DoorMesh->SetRelativeRotation(FRotator(CurrentRotation.Pitch, NewYaw, CurrentRotation.Roll));

		//Check if door reached target
		if (FMath::IsNearlyEqual(NewYaw, TargetYaw, 1.0f))
		{
			bIsMoving = false;
			bIsOpen = (TargetYaw != InitialYaw);
		}
	}
}


void ADoor::Interact(AActor* Interactor)
{
	//UE_LOG(LogTemp, Warning, TEXT("ADoor::Interact called by %s"), *Interactor->GetName());

	if (!Interactor) return;
	if (bIsMoving) return;

	AMyCharacter* Player = Cast<AMyCharacter>(Interactor);
	if (!Player) return;

	if (bIsLocked)
	{
		if (Player && Player->bHasKey)
		{
			if (UnlockedSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, UnlockedSound, GetActorLocation());
			}
			bIsLocked = false;
			return;
		}
		else
		{
			if (LockedSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, LockedSound, GetActorLocation());
			}

			return;
		}
	}

	bIsOpen = !bIsOpen;
	bIsMoving = true;

	if (bIsOpen)
	{	
		if (OpenSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, OpenSound, GetActorLocation());
		}

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
		if (CloseSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CloseSound, GetActorLocation());
		}

		TargetYaw = InitialYaw;
		//UE_LOG(LogTemp, Warning, TEXT("Door closed by %s"), *Interactor->GetName());
	}
}