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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	float MainIntensity = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	float GlowIntensity = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	float AttenuationRadius = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	float InnerConeAngle = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	FLinearColor FlashlightColor = FLinearColor(1.0f, 0.95f, 0.85f);

private:
	UPROPERTY()
	class USpotLightComponent* MainBeam;

	UPROPERTY()
	class USpotLightComponent* SoftGlow;

	bool bIsOn = false;


};
