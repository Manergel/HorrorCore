#include "UFlashlightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/Actor.h"

UFlashlightComponent::UFlashlightComponent()
{
    PrimaryComponentTick.bCanEverTick = false; // no per-frame work by default
}

void UFlashlightComponent::BeginPlay()
{
    Super::BeginPlay();

    AActor* MyOwner = GetOwner();
    if (!MyOwner) return;

    UCameraComponent* Camera = MyOwner->FindComponentByClass<UCameraComponent>();
    if (BeamMesh)
    {
        BeamMeshInstance = NewObject<UStaticMeshComponent>(MyOwner);
        BeamMeshInstance->SetStaticMesh(BeamMesh);

        BeamMeshInstance->AttachToComponent(Camera, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

        BeamMeshInstance->SetRelativeLocation(FVector(30.0f, 0.0f, 0.0f));
        BeamMeshInstance->SetRelativeRotation(FRotator::ZeroRotator);
        BeamMeshInstance->SetRelativeScale3D(FVector(BeamLength / 100.0f, BeamScale, BeamScale));

        BeamMeshInstance->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        BeamMeshInstance->SetCastShadow(false);
        BeamMeshInstance->RegisterComponent();

        if (BeamMaterial)
        {
            BeamMaterialInstance = UMaterialInstanceDynamic::Create(BeamMaterial, this);
            BeamMeshInstance->SetMaterial(0, BeamMaterialInstance);
            BeamMaterialInstance->SetVectorParameterValue(FName("BeamColor"), BeamColor);
            BeamMaterialInstance->SetScalarParameterValue(FName("BeamOpacity"), 0.0f);
        }

        BeamMeshInstance->SetVisibility(false);
    }
}


void UFlashlightComponent::ToggleFlashlight()
{
    bIsOn = !bIsOn;

    if (BeamMeshInstance && BeamMaterialInstance)
    {
        BeamMeshInstance->SetVisibility(bIsOn);
        BeamMaterialInstance->SetScalarParameterValue(FName("BeamOpacity"), bIsOn ? 1.0f : 0.0f);      
    }
}