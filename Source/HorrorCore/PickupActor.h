#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteractable.h"
#include "MyCharacter.h"
#include "InventoryComponent.h"
#include "PickupActor.generated.h"


UCLASS()
class HORRORCORE_API APickupActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	APickupActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	virtual void Interact(AActor* Interactor) override;

protected:
	virtual void BeginPlay() override;

public:

};
