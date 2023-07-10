// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CRPGAIPerceptionComponent.h"
#include "AI/CRPGAIController.h"
#include "Character/CRPGPlayerCharacter.h"
#include "Perception/AISense_Sight.h"


AActor* UCRPGAIPerceptionComponent::GetPlayerActor() const
{
	TArray<AActor*> PerceiveActors;

	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);
	if (PerceiveActors.Num() == 0)
	{
		return nullptr;
	}

	for (const auto PerceiveActor : PerceiveActors)
	{
		if (Cast<ACRPGPlayerCharacter>(PerceiveActor))
		{
			return PerceiveActor;
		}
	}

	return nullptr;
}
