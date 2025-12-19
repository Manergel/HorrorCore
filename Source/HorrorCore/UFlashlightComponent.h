#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Actor.h"
#include "UFlashlightComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HORRORCORE_API UFlashlightComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFlashlightComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	// Function to toggle flashlight on and off
	UFUNCTION(BlueprintCallable, Category = "Flashlight")
	void ToggleFlashlight();

private:

	// Spotlight component for the light effect
	UPROPERTY(VisibleAnywhere)
	USpotLightComponent* FlashlightSpotlight;

	// Boolean to track if flashlight is on
	bool bIsFlashlightOn;

	// Positioning and adjustments for the mesh
	UPROPERTY(EditAnywhere, Category = "Flashlight")
	FVector MeshOffset;

	// Flashlight intensity and range
	UPROPERTY(EditAnywhere, Category = "Flashlight")
	float LightIntensity;

	UPROPERTY(EditAnywhere, Category = "Flashlight")
	float LightRange;
};
