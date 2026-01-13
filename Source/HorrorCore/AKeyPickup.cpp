// Fill out your copyright notice in the Description page of Project Settings.


#include "AKeyPickup.h"
#include "MyCharacter.h"

// Sets default values
AAKeyPickup::AAKeyPickup()
{
	PrimaryActorTick.bCanEverTick = false;

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	RootComponent = KeyMesh;

}

// Called when the game starts or when spawned
void AAKeyPickup::BeginPlay()
{
	Super::BeginPlay();

}

void AAKeyPickup::Interact(AActor* Interactor)
{
	if (!Interactor) return;

	AMyCharacter* Player = Cast<AMyCharacter>(Interactor);
	if (Player)
	{
		Player->bHasKey = true;
	}

	if (PickupKey)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickupKey, GetActorLocation());
	}

	Destroy();
}

