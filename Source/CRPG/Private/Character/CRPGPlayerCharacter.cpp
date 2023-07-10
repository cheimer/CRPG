// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CRPGPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CRPGGameModeBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CRPGHealthComponent.h"
#include "Components/CRPGItemComponent.h"

ACRPGPlayerCharacter::ACRPGPlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SprintArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	ItemComponent = CreateDefaultSubobject<UCRPGItemComponent>("ItemComponent");

	bUseControllerRotationYaw = false;
	SpringArmComponent->TargetArmLength = FieldArmLength;
	SpringArmComponent->SetWorldRotation(FRotator(FieldCameraRotator));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->bInheritRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->RotationRate.Yaw = 270.0f;

}

void ACRPGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveUpDown", this, &ACRPGPlayerCharacter::MoveUpDown);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &ACRPGPlayerCharacter::MoveLeftRight);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACRPGPlayerCharacter::RunStart);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ACRPGPlayerCharacter::RunStop);
}

void ACRPGPlayerCharacter::RunStart()
{
	bRunStart = true;

	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ACRPGPlayerCharacter::RunStop()
{
	bRunStart = false;

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

bool ACRPGPlayerCharacter::IsRunning() const
{
	return bRunStart && !GetVelocity().IsZero();
}

void ACRPGPlayerCharacter::MoveUpDown(float amount)
{
	AddMovementInput(FVector(amount, 0.0f, 0.0f));
}

void ACRPGPlayerCharacter::MoveLeftRight(float amount)
{
	AddMovementInput(FVector(0.0f, amount, 0.0f));
}

void ACRPGPlayerCharacter::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	const auto HitCharacter = Cast<ACRPGBaseCharacter>(Other);
	if (HitCharacter && bSelfMoved) // 내가 가서 부딪힘
	{
		InBattleMode(Other);
	}

}

void ACRPGPlayerCharacter::InBattleMode(AActor* Other)
{
	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;
	GameMode->SetAICharacter(Other);
	GameMode->SetPlayerCharacter(this); 
	GameMode->ChangeMode(EScreenMode::Battle);

	GetCharacterMovement()->Deactivate();

	SpringArmComponent->TargetArmLength = BattleArmLength;

	FRotator BattleRotation = GetActorRotation();
	BattleRotation.Pitch = BattleCameraRotationPitch;
	SpringArmComponent->SetRelativeRotation(BattleRotation);
	SpringArmComponent->SetRelativeLocation(BattleCameraLocation);

	FVector OtherPosition = GetActorLocation() + GetActorForwardVector() * 200.0f + GetActorRightVector() * 200.0f;
	Other->SetActorLocation(OtherPosition);
	
	FRotator OtherRotation = UKismetMathLibrary::FindLookAtRotation(Other->GetActorLocation(), GetActorLocation());
	Other->SetActorRotation(OtherRotation);
	
	FRotator PlayerRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Other->GetActorLocation());
	SetActorRotation(PlayerRotation);

	AllMovementActivate(false);

	if (Cast<APlayerController>(GetController()))
	{
		Cast<APlayerController>(GetController())->bShowMouseCursor = true;
	}

	const auto Player = GameMode->GetPlayerCharacter();
	FString str = "Current Skill : ";
	str.Append(Skills[CurrentSkillIndex].Name.ToString());

	StatusStringSet(str);
}

void ACRPGPlayerCharacter::InFieldMode()
{
	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;
	GameMode->SetAICharacter(nullptr);
	GameMode->SetPlayerCharacter(this);
	GameMode->ChangeMode(EScreenMode::Field);
	GameMode->SetCurrentTurn(ETurnUser::Player);

	GetCharacterMovement()->Activate();

	SpringArmComponent->TargetArmLength = FieldArmLength;

	SpringArmComponent->SetRelativeRotation(FieldCameraRotator);
	SpringArmComponent->SetRelativeLocation(FVector::ZeroVector);

	AllMovementActivate(true);

	if (Cast<APlayerController>(GetController()))
	{
		Cast<APlayerController>(GetController())->bShowMouseCursor = false;
	}
}

void ACRPGPlayerCharacter::AllMovementActivate(bool IsActive)
{
	if (!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; It++)
	{
		if (It->Get() && It->Get()->GetPawn() && It->Get()->GetPawn()->GetMovementComponent())
		{
			if(IsActive)
				It->Get()->GetPawn()->GetMovementComponent()->Activate();
			else
				It->Get()->GetPawn()->GetMovementComponent()->Deactivate();
		}
	}

	
}

void ACRPGPlayerCharacter::OnDeath()
{
	Super::OnDeath();

	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	const auto GameMode = Cast<ACRPGGameModeBase>(GetWorld()->GetAuthGameMode());

	GameMode->ChangeMode(EScreenMode::GameOver);

}

void ACRPGPlayerCharacter::UseItem(FText ItemName)
{
	ItemComponent->UseItem(ItemName);

}
