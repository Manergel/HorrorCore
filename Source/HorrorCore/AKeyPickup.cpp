#include "AKeyPickup.h"
#include "MyCharacter.h"

// Sets default values
AAKeyPickup::AAKeyPickup()
{
	PrimaryActorTick.bCanEverTick = true;

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	RootComponent = KeyMesh;

	KeyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	InteractSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractSphere"));
	InteractSphere->SetupAttachment(RootComponent);

	InteractSphere->SetSphereRadius(40.f); // forgiving radius
	InteractSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractSphere->SetCollisionObjectType(ECC_WorldDynamic);

	// IMPORTANT: this sphere is ONLY for traces
	InteractSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractSphere->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	InteractSphere->SetGenerateOverlapEvents(false);
	InteractSphere->SetHiddenInGame(true);


}

// Called when the game starts or when spawned
void AAKeyPickup::BeginPlay()
{
	Super::BeginPlay();

}

void AAKeyPickup::Interact(AActor* Interactor)
{

	//UE_LOG(LogTemp, Warning, TEXT("KEY INTERACT CALLED"));

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


