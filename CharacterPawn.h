#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputSubsystems.h"
#include "CharacterPawn.generated.h"

UCLASS()
class SIXTH_API ACharacterPawn : public APawn
{
	GENERATED_BODY()

public:

	ACharacterPawn();

protected:

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
private:
	
	void MoveForward(const struct FInputActionValue& Value);
	void MoveRight(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);
	void Roll(const struct FInputActionValue& Value);
	void MoveUpDown(const struct FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USkeletalMeshComponent* MeshComponent;

	FVector Velocity;
	float MovementSpeed = 300.0f;
	float Gravity = -980.0f;
	bool bIsOnGround = false;

};
