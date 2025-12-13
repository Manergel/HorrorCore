#include "UFlashlightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInterface.h"

UFlashlightComponent::UFlashlightComponent()
{
    PrimaryComponentTick.bCanEverTick = false; // No tick per-frame, we only toggle flashlight
}

void UFlashlightComponent::BeginPlay()
{
    Super::BeginPlay();

    AActor* Owner = GetOwner();
    if (!Owner) return;

    // 1️⃣ Find the camera
    UCameraComponent* Camera = Owner->FindComponentByClass<UCameraComponent>();
    if (!Camera) return;

    // 2️⃣ Create beam mesh component
    BeamMeshComponent = NewObject<UStaticMeshComponent>(Owner);
    BeamMeshComponent->AttachToComponent(
        Camera,
        FAttachmentTransformRules::SnapToTargetNotIncludingScale
    );

    BeamMeshComponent->RegisterComponent();

    // 3️⃣ Assign mesh if provided
    if (BeamMeshAsset)
    {
        BeamMeshComponent->SetStaticMesh(BeamMeshAsset);
    }

    // 4️⃣ Assign material if provided
    if (BeamMaterial)
    {
        BeamMeshComponent->SetMaterial(0, BeamMaterial);
    }

    // 5️⃣ Position & scale like a flashlight
    BeamMeshComponent->SetRelativeLocation(FVector(30.f, 0.f, 0.f));
    BeamMeshComponent->SetRelativeRotation(FRotator::ZeroRotator);
    BeamMeshComponent->SetRelativeScale3D(FVector(10.f, 0.2f, 0.2f));

    // 6️⃣ Start OFF
    BeamMeshComponent->SetVisibility(false);
}


void UFlashlightComponent::ToggleFlashlight()
{
    bIsOn = !bIsOn;  // Toggle flashlight state

    if (BeamMeshComponent)
    {
        // Toggle the visibility of the flashlight beam
        BeamMeshComponent->SetVisibility(bIsOn);

        // Optionally, you can adjust intensity or any other property of the beam if needed
    }
}
