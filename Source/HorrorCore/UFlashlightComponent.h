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
	float MainIntensity = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	float AttenuationRadius = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	FLinearColor FlashlightColor = FLinearColor(1.0f, 0.95f, 0.85f);

private:
	UPROPERTY()
	class USpotLightComponent* MainBeam;

	bool bIsOn = false;


};
