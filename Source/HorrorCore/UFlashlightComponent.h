#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SpotLightComponent.h"
#include "UFlashlightComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HORRORCORE_API UFlashlightComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFlashlightComponent();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable)
    void ToggleFlashlight();

    UPROPERTY(EditAnywhere, Category = "Flashlight")
    UStaticMesh* BeamMeshAsset;

    UPROPERTY(EditAnywhere, Category = "Flashlight")
    UMaterialInterface* BeamMaterial;

private:
    UPROPERTY()
    UStaticMeshComponent* BeamMeshComponent;

    bool bIsOn = false;
};
