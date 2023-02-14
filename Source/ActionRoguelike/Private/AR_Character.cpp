// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AAR_Character::AAR_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

}

// Called when the game starts or when spawned
void AAR_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAR_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAR_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAR_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAR_Character::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

}

void AAR_Character::MoveForward(float value)
{
	//Get control rotation of this pawn, then zero X, Y to get only Z axis(forward), this avoid slow movement when camera in high position and pointing down to ground.
	FRotator CharacterControlRotation = GetControlRotation();
	CharacterControlRotation.Roll = 0.0f;
	CharacterControlRotation.Pitch = 0.0f;
	
	AddMovementInput(UKismetMathLibrary::GetForwardVector(CharacterControlRotation), value);
}

void AAR_Character::MoveRight(float value)
{
	FRotator CharacterControlRotation = GetControlRotation();
	CharacterControlRotation.Yaw = 0.0f;

	AddMovementInput(UKismetMathLibrary::GetRightVector(CharacterControlRotation), value);
}

