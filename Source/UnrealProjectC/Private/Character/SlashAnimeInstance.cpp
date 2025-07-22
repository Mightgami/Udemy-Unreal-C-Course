// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SlashAnimeInstance.h"
#include "Character/SlashCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void USlashAnimeInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	SlashCharacter = Cast<ASlashCharacter>(TryGetPawnOwner());
	if (SlashCharacter) {

		SlashCharacterMovement = SlashCharacter->GetCharacterMovement();
	}
}

void USlashAnimeInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);
	if (SlashCharacterMovement) {
		GroundSpeed = UKismetMathLibrary::VSizeXY(SlashCharacterMovement->Velocity);
		IsFalling = SlashCharacterMovement->IsFalling();
		CharacterState = SlashCharacter->GetCharacterState();
	}
}
