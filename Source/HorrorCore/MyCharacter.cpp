#include "MyCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Door.h"
#include "AKeyPickup.h"
//#include "IInteractable.h"


AMyCharacter::AMyCharacter()
{
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(RootComponent);
	FirstPersonCamera->bUsePawnControlRotation = true;

	FlashlightComponent = CreateDefaultSubobject<UFlashlightComponent>(TEXT("FlashlightComponent"));

	/*InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));*/
}


void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}


void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);

		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);

		EnhancedInput->BindAction(InteractAction, ETriggerEvent::Started, this, &AMyCharacter::Interact);

		EnhancedInput->BindAction(FlashlightAction, ETriggerEvent::Started, this, &AMyCharacter::ToggleFlashlight);

		EnhancedInput->BindAction(InventoryAction, ETriggerEvent::Started, this, &AMyCharacter::ToggleInventory);
	}
}

void AMyCharacter::Move(const FInputActionValue& Value) 
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}


void AMyCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxis = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxis.X);
		AddControllerPitchInput(-LookAxis.Y);
	}
}


void AMyCharacter::Interact(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Interact Input Received"));
	FVector Start = FirstPersonCamera->GetComponentLocation();
	FVector End = Start + FirstPersonCamera->GetForwardVector() * 300.f;

	//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.5f, 0, 1.f);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	// Trace forward from the camera
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		if (Hit.GetActor())
		{
			//UE_LOG(LogTemp, Warning, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());

			// Get the actual owner actor of the component hit
			ADoor* Door = Cast<ADoor>(Hit.GetActor());
			if (!Door && Hit.GetComponent())
			{
				Door = Cast<ADoor>(Hit.GetComponent()->GetOwner());
			}

			if (Door)
			{
				Door->Interact(this);
			}

		}
	}
}

void AMyCharacter::ToggleFlashlight()
{
	if (FlashlightComponent)
	{
		FlashlightComponent->ToggleFlashlight();
	}
}

void AMyCharacter::ToggleInventory()
{
	// DEBUG: Logging widget status
	UE_LOG(LogTemp, Warning, TEXT("ToggleInventory called. Instance=%p, Class=%s"), InventoryWidget, *GetNameSafe(InventoryWidgetClass));

	if (!InventoryWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryWidgetClass not set on %s"), *GetNameSafe(this));
		return;
	}

	// Create the widget if it doesn't exist, and remove it if it does
	if (InventoryWidget)
	{
		// Widget already exists, remove it
		InventoryWidget->RemoveFromViewport();
		InventoryWidget = nullptr;  // Reset widget reference
	}
	else
	{
		// Create the widget and add it to the viewport
		InventoryWidget = CreateWidget<UUserWidget>(GetWorld(), InventoryWidgetClass);
		if (InventoryWidget)
		{
			InventoryWidget->AddToViewport(100);  // Z-order 100, adjust as needed
		}

		// Switch input mode to Game and UI when inventory is opened
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FInputModeGameAndUI InputMode;
			InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PC->SetInputMode(InputMode);
			PC->bShowMouseCursor = true;
		}
	}
}