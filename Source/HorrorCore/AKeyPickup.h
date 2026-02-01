#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
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

	void Interact(AActor* Interactor);

	UPROPERTY(EditAnywhere, Category = "Key")
	UStaticMeshComponent* KeyMesh;

	UPROPERTY(EditAnywhere, Category = "Key")
	USoundBase* PickupKey;

	UPROPERTY(EditAnywhere)
	USoundBase* PickupSound;


};
