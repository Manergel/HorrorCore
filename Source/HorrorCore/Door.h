#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class HORRORCORE_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FrameMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, Category = "Door")
	float OpenAngle = 90.0f;
	UPROPERTY(EditAnywhere, Category = "Door")
	float OpenSpeed = 90.0f;

	bool bIsOpen = false;
	bool bIsMoving = false;
	float TargetYaw;
	float InitialYaw;

	UFUNCTION(BlueprintCallable)
	void Interact(AActor* Interactor);

};
