#include "UFlashlightComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UFlashlightComponent::UFlashlightComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// Set default values
	bIsFlashlightOn = false;
	LightIntensity = 5000.0f; // Intensity of the flashlight
	LightRange = 3000.0f; // Attenuation radius of the spotlight
}

// Called when the game starts
void UFlashlightComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (!Owner) return;

	UCameraComponent* Camera = Owner->FindComponentByClass<UCameraComponent>();

	if (Owner)
	{
		// Create Spotlight component dynamically
		FlashlightSpotlight = NewObject<USpotLightComponent>(Owner, USpotLightComponent::StaticClass(), TEXT("FlashlightSpotlight"));
		FlashlightSpotlight->RegisterComponent();  // Register spotlight component so it exists in the world
		FlashlightSpotlight->AttachToComponent(Camera, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		FlashlightSpotlight->SetRelativeLocation(MeshOffset);
		FlashlightSpotlight->SetIntensity(LightIntensity);
		FlashlightSpotlight->SetAttenuationRadius(LightRange);
		FlashlightSpotlight->SetOuterConeAngle(25.0f); // Angle of the outer cone of the spotlight
		FlashlightSpotlight->SetInnerConeAngle(12.0f); // Angle of the inner cone of the spotlight
		FlashlightSpotlight->SetLightColor(FLinearColor(1.0f, 0.95f, 0.85f)); // Slightly yellow light
		FlashlightSpotlight->SetVisibility(false); // Initially turn off the spotlight
	}

}

// Toggle the flashlight on and off
void UFlashlightComponent::ToggleFlashlight()
{
	bIsFlashlightOn = !bIsFlashlightOn;

	// If flashlight is on, show light, otherwise hide
	if (bIsFlashlightOn)
	{
		FlashlightSpotlight->SetVisibility(true);
	}
	else
	{
		FlashlightSpotlight->SetVisibility(false);
	}
}
