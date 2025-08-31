#include "UFlashlightComponent.h"
#include "Components/SpotLightComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"

UFlashlightComponent::UFlashlightComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	MainBeam = nullptr;

}

void UFlashlightComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* MyOwner = GetOwner())
	{
		if (UCameraComponent* Camera = MyOwner->FindComponentByClass<UCameraComponent>())
		{	
			MainBeam = NewObject<USpotLightComponent>(MyOwner, USpotLightComponent::StaticClass(), TEXT("MainFlaslightBeam"));
			if (MainBeam)
			{
				MainBeam->AttachToComponent(Camera, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				MainBeam->RegisterComponent();
				MainBeam->SetRelativeLocation(FVector(30.0f, 0.0f, 0.0f));
				MainBeam->SetRelativeRotation(FRotator::ZeroRotator);

				MainBeam->SetIntensity(0.0f);
				MainBeam->SetOuterConeAngle(30.0f);
				MainBeam->SetInnerConeAngle(15.0f);
				MainBeam->SetLightFalloffExponent(6.0f);
				MainBeam->SetAttenuationRadius(AttenuationRadius);
				MainBeam->bUseInverseSquaredFalloff = false;
				MainBeam->SetLightColor(FLinearColor(1.0f, 0.9f, 0.7f));
			}

		}
	}
}

void UFlashlightComponent::ToggleFlashlight()
{
	bIsOn = !bIsOn;

	if (MainBeam) MainBeam->SetIntensity(bIsOn ? MainIntensity : 0.0f);
	

	UE_LOG(LogTemp, Warning, TEXT("Flashlight %s"), bIsOn ? TEXT("ON") : TEXT("OFF"));
}

