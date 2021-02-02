// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT300MAIN_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Health Changing Methods
	UFUNCTION(BlueprintCallable)
		void AddHealth(int value);
	UFUNCTION(BlueprintCallable)
		void SubtractHealth(int value);
	void LifeDrain();

	//Health Variables
	UPROPERTY(BlueprintReadWrite)
		int CurrentHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int StartingHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxHealth = 300;

	//Defence
	UPROPERTY(BlueprintReadWrite)
		int CurrentDefence = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int StartingDefence = 0;

	//Life Drain Variables
	UPROPERTY(EditAnywhere)
		int DrainAmount = 5;
	//Rate at which health drains 
	UPROPERTY(EditAnywhere)
		float DrainRate = 1;

	UPROPERTY(BlueprintReadOnly)
		bool IsDead = false;

protected:
	virtual void BeginPlay() override;

};
