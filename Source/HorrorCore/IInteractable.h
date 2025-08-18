#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractable.generated.h"

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class HORRORCORE_API IInteractable
{
	GENERATED_BODY()

public:
	virtual void Interact(AActor* Caller) = 0;
};
