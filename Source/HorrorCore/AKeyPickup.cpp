// Fill out your copyright notice in the Description page of Project Settings.


#include "AKeyPickup.h"

// Sets default values
AAKeyPickup::AAKeyPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAKeyPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAKeyPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

