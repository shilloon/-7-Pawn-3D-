#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PGPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class SIXTH_API APGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APGPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Input")
	class UInputAction* IA_MoveForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Input")
	class UInputAction* IA_MoveRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Input")
	class UInputAction* IA_Look;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* IA_Roll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* IA_MoveUpDown;

	virtual void BeginPlay() override;

};
