#include "UFlashlightComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"

UFlashlightComponent::UFlashlightComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	Flashlight = nullptr;

}

void UFlashlightComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* MyOwner = GetOwner())
	{
		UCameraComponent* Camera = MyOwner->FindComponentByClass<UCameraComponent>();
		if (Camera)
		{
			Flashlight = NewObject<USpotLightComponent>(MyOwner);
			Flashlight->RegisterComponent();
			Flashlight->AttachToComponent(Camera, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			Flashlight->SetRelativeLocation(FVector(30.0f, 0.0f, 0.0f));
			Flashlight->SetRelativeRotation(FRotator::ZeroRotator);

			Flashlight->SetIntensity(0.0f);
			Flashlight->SetOuterConeAngle(35.0f);
			Flashlight->SetInnerConeAngle(12.0f);
			Flashlight->SetLightFalloffExponent(4.0f);
			Flashlight->SetCastShadows(true);
			Flashlight->bCastVolumetricShadow = true;
			Flashlight->bUseInverseSquaredFalloff = false;
			Flashlight->SetAttenuationRadius(800.0f);
			Flashlight->SetLightColor(FLinearColor(1.0f, 0.95f, 0.85f));

		}
	}
}

void UFlashlightComponent::ToggleFlashlight()
{
	if (!Flashlight) return;
	bIsOn = !bIsOn;
	Flashlight->SetIntensity(bIsOn ? Intensity : 0.0f);

	//UE_LOG(LogTemp, Warning, TEXT("Flashlight %s"), bIsOn ? TEXT("ON") : TEXT("OFF"));
}

