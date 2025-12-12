#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

private:
	UPROPERTY()
	class UStaticMeshComponent* BeamMeshInstance = nullptr;

	UPROPERTY()
	class UMaterialInstanceDynamic* BeamMaterialInstance = nullptr;

	bool bIsOn = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flashlight")
	UStaticMesh* BeamMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	UMaterialInterface* BeamMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	float BeamLength = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	float BeamScale = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	FLinearColor BeamColor = FLinearColor(1.0f, 0.95f, 0.8f);
};
