// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	//setting health at start of game
	CurrentHealth = StartingHealth;
	UE_LOG(LogTemp, Warning, TEXT("Current Health : %d"), CurrentHealth);

	//setting defence at the start of game
	CurrentDefence = StartingDefence;
	UE_LOG(LogTemp, Warning, TEXT("Current Defence : %d"), CurrentDefence);

	//Timer calling Life Drain method every second
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UHealthComponent::LifeDrain, DrainRate, true, 0);
}

void UHealthComponent::AddHealth(int value)
{
	CurrentHealth += value;
	UE_LOG(LogTemp, Warning, TEXT("%d"), CurrentHealth);
}

void UHealthComponent::SubtractHealth(int value)
{
	CurrentHealth -= value;
	UE_LOG(LogTemp, Warning, TEXT("%d"), CurrentHealth);

	if (CurrentHealth <= 0)
	{
		IsDead = true;
		UE_LOG(LogTemp, Warning, TEXT("Dead"));
	}
}

//Drains CurrentHealth if it is over maximum
void UHealthComponent::LifeDrain()
{
	if (CurrentHealth > MaxHealth)
	{
		//Checks if the drain value wont cut into main healthbar than removes extra health
		if ((CurrentHealth - DrainAmount) < MaxHealth)
		{
			CurrentHealth = MaxHealth;
		}
		else
		{
			CurrentHealth -= DrainAmount;
		}
		UE_LOG(LogTemp, Warning, TEXT("%d"), CurrentHealth);
	}
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

