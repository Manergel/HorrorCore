//#include "PickupActor.h"
//
//APickupActor::APickupActor()
//{
//	PrimaryActorTick.bCanEverTick = false;
//
//	Object = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object"));
//	RootComponent = Object;
//}
//
//void APickupActor::BeginPlay()
//{
//	Super::BeginPlay();
//}

//void APickupActor::Interact(AActor* Interactor)
//{
//	if (Interactor)
//	{
//		UInventoryComponent* Inventory = Interactor->FindComponentByClass<UInventoryComponent>();
//		if (Inventory)
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Found Inventory"));
//			Inventory->AddItem(ItemID);
//		}
//
//	}
//	//if (AMyCharacter* Player = Cast<AMyCharacter>(Interactor))
//	//{
//	//	Player->AddKey();
//	//}
//	UE_LOG(LogTemp, Warning, TEXT("Picked up by %s"), *Interactor->GetName());
//
//	Destroy();
//}



