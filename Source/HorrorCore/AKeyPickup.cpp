#include "AKeyPickup.h"
#include "MyCharacter.h"

// Sets default values
AAKeyPickup::AAKeyPickup()
{
	PrimaryActorTick.bCanEverTick = true;

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	RootComponent = KeyMesh;

	KeyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AAKeyPickup::BeginPlay()
{
	Super::BeginPlay();

}

void AAKeyPickup::Interact(AActor* Interactor)
{

	UE_LOG(LogTemp, Warning, TEXT("KEY INTERACT CALLED"));

	AMyCharacter* Player = Cast<AMyCharacter>(Interactor);
	if (!Player) return;

	if (Player)
	{
		Player->bHasKey = true;
	}

	const float MaxPickupDistance = 150.f;

	float Distance = FVector::Dist
	(
		Player->GetActorLocation(),
		GetActorLocation()
	);

	if (Distance > MaxPickupDistance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Key too far away"));
		return;
	}

	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
	}

	Destroy();
}


