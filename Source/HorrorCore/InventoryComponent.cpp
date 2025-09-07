#include "InventoryComponent.h"
#include "PickupActor.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInventoryComponent::AddItem(FName ItemID)
{
	Items.Add(ItemID);
	UE_LOG(LogTemp, Warning, TEXT("Item added: %s"), *ItemID.ToString());
}



