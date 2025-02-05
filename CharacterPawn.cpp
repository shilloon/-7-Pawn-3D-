#include "CharacterPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PGPlayerController.h"

ACharacterPawn::ACharacterPawn()
{

	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->InitCapsuleSize(37.0f, 96.0f);
	CapsuleComponent->SetCollisionProfileName(TEXT("Pawn"));
	RootComponent = CapsuleComponent;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CapsuleComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetSimulatePhysics(false);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(CapsuleComponent);
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bUsePawnControlRotation = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

}

void ACharacterPawn::BeginPlay()
{

	Super::BeginPlay();

}

void ACharacterPawn::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if (!bIsOnGround)
	{

		Velocity.Z += Gravity * DeltaTime;

	}

	FVector NewLocation = GetActorLocation() + Velocity * DeltaTime;
	SetActorLocation(NewLocation);

	FHitResult HitResult;
	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0, 0, 90);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

	if (bHit)
	{

		bIsOnGround = true;
		Velocity.Z = 0;

	}
	else
	{

		bIsOnGround = false;

	}
}

void ACharacterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{

		if (APGPlayerController* PlayerController = Cast<APGPlayerController>(GetController()))
		{

			if (PlayerController->IA_MoveForward)
			{

				EnhancedInputComponent->BindAction(PlayerController->IA_MoveForward, ETriggerEvent::Triggered, this, &ACharacterPawn::MoveForward);

			}
			if (PlayerController->IA_MoveRight)
			{

				EnhancedInputComponent->BindAction(PlayerController->IA_MoveRight, ETriggerEvent::Triggered, this, &ACharacterPawn::MoveRight);

			}
			if (PlayerController->IA_Look)
			{

				EnhancedInputComponent->BindAction(PlayerController->IA_Look, ETriggerEvent::Triggered, this, &ACharacterPawn::Look);

			}
			if (PlayerController->IA_Roll)
			{

				EnhancedInputComponent->BindAction(PlayerController->IA_Roll, ETriggerEvent::Triggered, this, &ACharacterPawn::Roll);

			}
			if (PlayerController->IA_MoveUpDown)
			{

				EnhancedInputComponent->BindAction(PlayerController->IA_MoveUpDown, ETriggerEvent::Triggered, this, &ACharacterPawn::MoveUpDown);

			}
		}

	}

}

void ACharacterPawn::MoveForward(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();  
	if (Controller && AxisValue != 0.0f)
	{
		float SpeedFactor = (bIsOnGround) ? 1.0f : 0.3f;

		FRotator ControlRotation = GetControlRotation();
		ControlRotation.Pitch = 0.0f;

		FVector ForwardVector = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::Y);
	
		AddActorLocalOffset(ForwardVector * AxisValue * 300.0f * SpeedFactor * GetWorld()->GetDeltaSeconds(), false);

	}
}

void ACharacterPawn::MoveRight(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();  
	if (Controller && AxisValue != 0.0f)
	{

		FRotator ControlRotation = GetControlRotation();
		ControlRotation.Pitch = 0.0f;
		ControlRotation.Roll = 0.0f;
		
		FVector RightVector = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::X);
		float SpeedFactor = (bIsOnGround) ? 1.0f : 0.3f;
		AddActorLocalOffset(RightVector * AxisValue * 300.0f * SpeedFactor *GetWorld()->GetDeltaSeconds(), false);
	}
}

void ACharacterPawn::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisValue = Value.Get<FVector2D>();
	if (Controller)
	{
		
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += LookAxisValue.X * 2.f;
		SetActorRotation(NewRotation);

		FRotator CameraRotation = CameraComponent->GetComponentRotation();
		CameraRotation.Pitch = FMath::Clamp(CameraRotation.Pitch + LookAxisValue.Y * 2.f, -30.f, 30.f);
		CameraComponent->SetWorldRotation(CameraRotation);

	}
}

void ACharacterPawn::Roll(const FInputActionValue& Value)
{

	float AxisValue = Value.Get<float>();

	if (AxisValue != 0.0f)
	{

		FRotator RotationDelta = FRotator(0.f, 0.f, AxisValue * 2.f);

		AddActorLocalRotation(RotationDelta, true);

	}

}

void ACharacterPawn::MoveUpDown(const FInputActionValue& Value)
{

	float AxisValue = Value.Get<float>();

	if (FMath::Abs(AxisValue) > KINDA_SMALL_NUMBER)
	{

		float SpeedFactor = (bIsOnGround) ? 1.0f : 0.3f;
		Velocity.Z = AxisValue * 300.0f * SpeedFactor;

	}
	else
	{

		Velocity.Z = FMath::FInterpTo(Velocity.Z, 0.0f, GetWorld()->GetDeltaSeconds(), 3.0f);

	}

}