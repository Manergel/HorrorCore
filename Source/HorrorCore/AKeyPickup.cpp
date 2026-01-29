// Fill out your copyright notice in the Description page of Project Settings.


#include "AKeyPickup.h"
#include "MyCharacter.h"

// Sets default values
AAKeyPickup::AAKeyPickup()
{
	PrimaryActorTick.bCanEverTick = false;

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	RootComponent = KeyMesh;

	PickupSphere = CreateDefaultSubobject<USphereComponent>("PickupSphere");
	PickupSphere->SetupAttachment(KeyMesh);
	PickupSphere->SetSphereRadius(70.f);
	PickupSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	PickupSphere->OnComponentBeginOverlap.AddDynamic
	(
		this, &AAKeyPickup::OnPickup
	);

}

// Called when the game starts or when spawned
void AAKeyPickup::BeginPlay()
{
	Super::BeginPlay();

}


void AAKeyPickup::OnPickup
(
	UPrimitiveComponent*,
	AActor* OtherActor,
	UPrimitiveComponent*,
	int32,
	bool,
	const FHitResult&
)

{
	AMyCharacter* Player = Cast<AMyCharacter>(OtherActor);
	if (!Player) return;

	if (Player)
	{
		Player->bHasKey = true;
	}

	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
	}

	Destroy();
}


