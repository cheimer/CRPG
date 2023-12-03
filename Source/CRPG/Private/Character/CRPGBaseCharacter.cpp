// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CRPGBaseCharacter.h"
#include "Components/CRPGHealthComponent.h"
#include "Components/CRPGAttackComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/CRPGAttackAnimNotify.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "CRPGGameModeBase.h"
#include "UI/CRPGPlayerBattleWidget.h"

ACRPGBaseCharacter::ACRPGBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UCRPGHealthComponent>("HealthComponent");
	AttackComponent = CreateDefaultSubobject<UCRPGAttackComponent>("AttackComponent");
}

void ACRPGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(AttackComponent);
	
	HealthComponent->OnDeathSignature.AddUObject(this, &ACRPGBaseCharacter::OnDeath);
	HealthComponent->OnHealthChangeSignature.AddUObject(this, &ACRPGBaseCharacter::OnHealthChange);

	auto AttackNotify = AnimUtils::FindNotifyByClass<UCRPGAttackAnimNotify>(AttackAnim);
	if (!AttackNotify) return;

	AttackNotify->OnNotifySignature.AddUObject(this, &ACRPGBaseCharacter::PlayDamagedAnim);

	for (int idx = 0; idx < Skills.Num(); idx++)
	{
		Skills[idx].LeftCount = Skills[idx].MaxCount;
		Skills[idx].LeftCool = 0;
		Skills[idx].SkillIndex = idx;
	}
	SkillNum = Skills.Num();
	CurrentSkillIndex = 0;
}

void ACRPGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 임시 조치
	if (CurrentSkillIndex == SkillNum)
	{
		CurrentSkillIndexReset();
	}
}

void ACRPGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ACRPGBaseCharacter::GetDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;

	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

	return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z);
}

bool ACRPGBaseCharacter::IsRunning() const
{
	return false;
}

void ACRPGBaseCharacter::OnDeath()
{
	PlayAnimMontage(DeathAnim);

	GetCharacterMovement()->DisableMovement();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetLifeSpan(LifeSpanTime);
}

void ACRPGBaseCharacter::OnHealthChange(AActor* DamageCauser, AActor* DamagedActor)
{

}

void ACRPGBaseCharacter::PlayAttackAnim()
{
	PlayAnimMontage(AttackAnim);

}

void ACRPGBaseCharacter::PlayDamagedAnim(USkeletalMeshComponent* MeshComponent)
{
	if (!GetWorld()) return;
	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto AnimInstance = GetMesh()->GetAnimInstance();

	bool EnemyOrMe = UKismetMathLibrary::EqualEqual_ObjectObject(this, GameMode->GetAICharacter()) || 
		UKismetMathLibrary::EqualEqual_ObjectObject(this, GameMode->GetPlayerCharacter());

	if (HealthComponent->IsDead() || !AnimInstance || AnimInstance->IsAnyMontagePlaying() || !EnemyOrMe)
		return;

	int32 RandInt = FMath::RandRange(0, 2);
	if (DamagedAnimArray[RandInt])
	{
		PlayAnimMontage(DamagedAnimArray[RandInt]);
	}
}


void ACRPGBaseCharacter::ChangeCurrentSkill(int32 Idx)
{
	if (!CanUseSkill(Idx))
		return;

	FString str = "Current Skill : ";
	str.Append(Skills[Idx].Name.ToString());

	StatusStringSet(str);
	CurrentSkillIndex = Idx;
}

bool ACRPGBaseCharacter::UseSkill()
{
	if (!CanUseSkill(CurrentSkillIndex))
		return false;

	for (int i = 0; i < SkillNum; i++)
	{
		if (Skills[i].LeftCool != 0)
		{
			Skills[i].LeftCool--;
		}
	}

	Skills[CurrentSkillIndex].LeftCount--;
	Skills[CurrentSkillIndex].LeftCool = Skills[CurrentSkillIndex].CoolTime;

	return true;
}

bool ACRPGBaseCharacter::CanUseSkill(int Index)
{
	if (Skills[Index].Limited && Skills[Index].LeftCount <= 0)
	{
		FString str = "Not Remain Skill Count\n";
		str.Append("Current Skill : ");
		str.Append(Skills[CurrentSkillIndex].Name.ToString());

		StatusStringSet(str);
		return false;
	}
	if (Skills[Index].LeftCool > 0)
	{
		FString str = "Skill Cool Unready ";
		str.Append(FString::FromInt(Skills[Index].LeftCool));
		str.Append(" / ");
		str.Append(FString::FromInt(Skills[Index].CoolTime));
		str.Append("\nCurrent Skill : ");
		str.Append(Skills[CurrentSkillIndex].Name.ToString());

		StatusStringSet(str);
		return false;
	}

	return true;
}
