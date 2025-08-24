#include "UFlashlightComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"

UFlashlightComponent::UFlashlightComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Flashlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight"));
	Flashlight->SetupAttachment(nullptr);
	Flashlight->SetIntensity(0.0f);
	Flashlight->SetOuterConeAngle(30.0f);
	Flashlight->bUseInverseSquaredFalloff = false;
	Flashlight->SetAttenuationRadius(800.0f);

}

void UFlashlightComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* MyOwner = GetOwner())
	{
		UCameraComponent* Camera = MyOwner->FindComponentByClass<UCameraComponent>();
		if (Camera)
		{
			Flashlight->AttachToComponent(Camera, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			Flashlight->SetRelativeLocation(FVector(30.0f, 0.0f, 0.0f));
			Flashlight->SetRelativeRotation(FRotator::ZeroRotator);
		}
	}
}

void UFlashlightComponent::ToggleFlashlight()
{
	bIsOn = !bIsOn;
	Flashlight->SetIntensity(bIsOn ? Intensity : 0.0f);

	UE_LOG(LogTemp, Warning, TEXT("Flashlight %s"), bIsOn ? TEXT("ON") : TEXT("OFF"));
}

