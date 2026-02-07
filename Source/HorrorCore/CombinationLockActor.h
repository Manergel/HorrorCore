#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CombinationLockActor.generated.h"

UCLASS()
class HORRORCORE_API ACombinationLockActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACombinationLockActor();

	UFUNCTION(BlueprintCallable)
	void AdjustDigit(int32 Delta);

	UFUNCTION(BlueprintCallable)
	void CycleDigit(int32 Delta);

	UFUNCTION(BlueprintCallable, Category = "Lock")
	void ConfirmCode();

	UFUNCTION()
	void BeginUse(APawn* UsingPawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock")
	int32 SelectedIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock")
	int32 EnteredCode = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock")
	TArray<int32> CurrentCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock")
	TArray<int32> CorrectCode;

	UPROPERTY(BlueprintReadWrite, Category = "Lock")
	bool bIsSolved = false;

	void PrintCode() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lock")
	class UPointLightComponent* LockLight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock")
	FLinearColor RedColor = FLinearColor::Red;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock")
	FLinearColor GreenColor = FLinearColor::Green;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* InteractionBox;

	
};
