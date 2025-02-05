#include "PGGameMode.h"
#include "CharacterPawn.h"
#include "PGPlayerController.h"

APGGameMode::APGGameMode()
{

	DefaultPawnClass = ACharacterPawn::StaticClass();
	PlayerControllerClass = APGPlayerController::StaticClass();

}

