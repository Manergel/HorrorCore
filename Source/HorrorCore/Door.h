#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteractable.h"
#include "Door.generated.h"

UCLASS()
class HORRORCORE_API ADoor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ADoor();

	virtual void Interact(AActor* Caller) override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, Category = "Door")
	float OpenAngle = 90.0f;

	UPROPERTY(EditAnywhere, Category = "Door")
	float OpenSpeed = 2.0f;

	bool bIsOpen = false;
	float CurrentAlpha = 0.0f;
	float TargetAlpha = 0.0f;

};
