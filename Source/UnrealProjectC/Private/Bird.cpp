// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"
#include <Components/CapsuleComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ABird::ABird()
{

	// Don't rotate when the controller rotates. Let that just affect the camera.


 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetCapsuleHalfHeight(20.0f);
	Capsule->SetCapsuleRadius(15.0f);
	SetRootComponent(Capsule);
	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
	BirdMesh->SetupAttachment(GetRootComponent());
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.0f; //
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);

	//AutoPossessPlayer = EAutoReceiveInput::Player0;
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(BirdMappingContext, 0);
		}
	}

}

void ABird::Move(const FInputActionValue& Value)
{
	const FVector2D direction = Value.Get<FVector2D>();
	if (Controller) {
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, direction.X);
		//AddMovementInput(RightDirection, MovementVector.X);
	}
	
}

void ABird::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxesValue = Value.Get<FVector2D>();
	if (Controller) {
		FVector Forward = GetActorForwardVector();
		AddControllerYawInput(LookAxesValue.X);
		AddControllerPitchInput(LookAxesValue.Y);

	}

}

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABird::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABird::Look);

	}

}

