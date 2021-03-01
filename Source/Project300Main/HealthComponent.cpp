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

	//setting stamina at start of game
	CurrentStamina = MaxStamina;
	UE_LOG(LogTemp, Warning, TEXT("Current Stamina : %d"), CurrentStamina);

	//Timer calling Life Drain Function
	FTimerHandle LifeDrainTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(LifeDrainTimerHandle, this, &UHealthComponent::LifeDrain, DrainRate, true, 0);

	//Timer calling RegenStamina Function
	FTimerHandle StaminaTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(StaminaTimerHandle, this, &UHealthComponent::RegenStamnina, StaminaRegenRate, true, 0);
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

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
		UE_LOG(LogTemp, Warning, TEXT("Current Health : %d"), CurrentHealth);
	}
}

//Regens Stamina if it is not at max
void UHealthComponent::RegenStamnina()
{
	if (CurrentStamina < MaxStamina)
	{
		if ((CurrentStamina + StaminaRegenAmount) > MaxStamina)
		{
			CurrentStamina = MaxStamina;
		}
		else
		{
			CurrentStamina += StaminaRegenAmount;
		}
		UE_LOG(LogTemp, Warning, TEXT("Current Stamina : %d"), CurrentStamina);
	}
}

void UHealthComponent::SubtractStamina(int amount)
{
	if ((CurrentStamina - amount) < 0)
	{
		CurrentStamina = 0;
	}
	else
	{
		CurrentStamina -= amount;
	}
}

void UHealthComponent::AddStamina(int amount)
{
	if ((CurrentStamina + amount) > MaxStamina)
	{
		CurrentStamina = MaxStamina;
	}
	else
	{
		CurrentStamina += amount;
	}
}


