#include "PGPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

APGPlayerController::APGPlayerController()
    :   InputMappingContext(nullptr),
        IA_MoveForward(nullptr),
        IA_MoveRight(nullptr),
        IA_Look(nullptr),
        IA_Roll(nullptr),
        IA_MoveUpDown(nullptr)
{   
}

void APGPlayerController::BeginPlay()
{

    Super::BeginPlay();

    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {

        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {

            if (InputMappingContext)
            {

                Subsystem->AddMappingContext(InputMappingContext, 0);

            }

        }

    }

}