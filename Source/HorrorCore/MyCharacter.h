#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "UFlashlightComponent.h"
#include "MyCharacter.generated.h"

class UInventoryComponent;
class UUserWidget;
class ACombinationLockActor;

UCLASS()
class HORRORCORE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	AMyCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;
	
	void Interact(const FInputActionValue& Value);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* InteractAction;

	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;

	UFUNCTION()
	void Look(const FInputActionValue& Value);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	class UFlashlightComponent* FlashlightComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* FlashlightAction;

	UFUNCTION()
	void ToggleInventory();
	UFUNCTION()
	void ToggleFlashlight();

	UPROPERTY()
	ACombinationLockActor* ActiveLock = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> InventoryWidgetClass;
	UPROPERTY()
	UUserWidget* InventoryWidget = nullptr;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	//UInventoryComponent* InventoryComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* InventoryAction;

public:

	UPROPERTY(BlueprintReadWrite, Category = "Keys")
	bool bHasKey = false;

};
