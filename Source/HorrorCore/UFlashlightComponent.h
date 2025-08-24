#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	UPROPERTY(VisibleAnywhere)
	class USpotLightComponent* Flashlight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* FlashlightAction;
	float Intensity = 5000.0f;

	bool bIsOn = false;

private:


};
