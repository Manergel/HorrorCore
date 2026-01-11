// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AKeyPickup.generated.h"

UCLASS()
class HORRORCORE_API AAKeyPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAKeyPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Key")
	UStaticMesh* KeyMesh;

	UPROPERTY(EditAnywhere, Category = "Key")
	USoundBase* PickupKey;

	UFUNCTION(BlueprintCallable)
	void Interact(AActor* Interactor);

};
