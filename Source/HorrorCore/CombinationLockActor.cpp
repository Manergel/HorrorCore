#include "CombinationLockActor.h"
#include "Components/PointLightComponent.h"

ACombinationLockActor::ACombinationLockActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(Root);
	InteractionBox->SetBoxExtent(FVector(15.f, 15.f, 15.f));


	LockLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("LockLight"));
	LockLight->SetupAttachment(RootComponent);
	LockLight->SetIntensity(5000.f);
	LockLight->SetLightColor(RedColor);

}

// Called when the game starts or when spawned
void ACombinationLockActor::BeginPlay()
{
	Super::BeginPlay();

	CurrentCode = { 0,0,0,0 };
	CorrectCode = { 5,2,1,7 };

	PrintCode();
	
}

// Called every frame
void ACombinationLockActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACombinationLockActor::AdjustDigit(int32 Delta)
{
	if (bIsSolved)
		return;

	CurrentCode[SelectedIndex] += Delta;

	if (CurrentCode[SelectedIndex] > 9)
	{
		CurrentCode[SelectedIndex] = 0;
	}

	else if (CurrentCode[SelectedIndex] < 0)
	{
		CurrentCode[SelectedIndex] = 9;
	}

	PrintCode();
}

void ACombinationLockActor::CycleDigit(int32 Direction)
{
	if (bIsSolved)
		return;

	SelectedIndex = (SelectedIndex + Direction + CurrentCode.Num()) % CurrentCode.Num();
	PrintCode();
}

void ACombinationLockActor::ConfirmCode()
{
	if (CurrentCode == CorrectCode)
	{
		bIsSolved = true;
		LockLight->SetLightColor(GreenColor);
		UE_LOG(LogTemp, Warning, TEXT("[LOCK] SOLVED!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[LOCK] WRONG CODE"));
	}
}

void ACombinationLockActor::PrintCode()const
{
	UE_LOG(LogTemp, Warning, TEXT("[LOCK] Code: %d %d %d %d | Selected: %d"),
		CurrentCode[0], CurrentCode[1], CurrentCode[2], CurrentCode[3], SelectedIndex);
}

void ACombinationLockActor::BeginInteraction(class AMyCharacter* Player)
{
	ActivePlayer = Player;
	UE_LOG(LogTemp, Warning, TEXT("Lock engaged"));
}

void ACombinationLockActor::EndInteraction()
{
	ActivePlayer = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("Lock interaction ended"));
}