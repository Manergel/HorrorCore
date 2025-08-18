#include "Door.h"
#include "Engine/Engine.h"

ADoor::ADoor()
{

	PrimaryActorTick.bCanEverTick = false;

}

void ADoor::Interact(AActor* Caller)
{
	UE_LOG(LogTemp, Warning, TEXT("The door creaks open!"));
}


//void ADoor::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//
//void ADoor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

