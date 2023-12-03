// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CRPGAIController.generated.h"

class UCRPGAIPerceptionComponent;

UCLASS()
class CRPG_API ACRPGAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ACRPGAIController();

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UCRPGAIPerceptionComponent* CRPGAIPerceptionComponent;

private:
	AActor* GetFocusOnActor() const;

};
