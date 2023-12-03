// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CRPGAttackAnimNotify.h"

void UCRPGAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotifySignature.Broadcast(MeshComp);

	Super::Notify(MeshComp, Animation);
}