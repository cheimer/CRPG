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
<<<<<<< HEAD
		if (Cast<ACRPGPlayerCharacter>(PerceiveActor))
=======
		if (Cast<ACRPGPlayerCharacter>(PerceiveActor) != nullptr)
>>>>>>> fcfe033b76efe3c95649eaa2aec3622638e0ea57
		{
			return PerceiveActor;
		}
	}

	return nullptr;
}
