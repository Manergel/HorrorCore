#include "UFlashlightComponent.h"
#include "Components/SpotLightComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"

UFlashlightComponent::UFlashlightComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	MainBeam = nullptr;
	SoftGlow = nullptr;

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
				MainBeam->SetOuterConeAngle(25.0f);
				MainBeam->SetInnerConeAngle(15.0f);
				MainBeam->SetLightFalloffExponent(6.0f);
				MainBeam->SetAttenuationRadius(AttenuationRadius);
				MainBeam->bUseInverseSquaredFalloff = false;
				MainBeam->SetLightColor(FLinearColor(1.0f, 0.9f, 0.7f));
			}

			SoftGlow = NewObject<USpotLightComponent>(MyOwner, USpotLightComponent::StaticClass(), TEXT("FlashlightGlow"));
			if (SoftGlow)
			{
				SoftGlow->AttachToComponent(Camera, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				SoftGlow->RegisterComponent();
				SoftGlow->SetRelativeLocation(FVector(30.0f, 0.0f, 0.0f));
				SoftGlow->SetRelativeRotation(FRotator::ZeroRotator);

				SoftGlow->SetIntensity(0.0f);
				SoftGlow->SetOuterConeAngle(60.0f);
				SoftGlow->SetInnerConeAngle(30.0f);
				SoftGlow->SetLightFalloffExponent(3.0f);
				SoftGlow->SetAttenuationRadius(AttenuationRadius * 1.2f);
				SoftGlow->bUseInverseSquaredFalloff = false;
				SoftGlow->SetLightColor(FLinearColor(1.0f, 0.85f, 0.65f));
			}

		}
	}
}

void UFlashlightComponent::ToggleFlashlight()
{
	bIsOn = !bIsOn;

	if (MainBeam) MainBeam->SetIntensity(bIsOn ? MainIntensity : 0.0f);
	
	if (SoftGlow) SoftGlow->SetIntensity(bIsOn ? GlowIntensity * 0.5f : 0.0f);

	UE_LOG(LogTemp, Warning, TEXT("Flashlight %s"), bIsOn ? TEXT("ON") : TEXT("OFF"));
}

