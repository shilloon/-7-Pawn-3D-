플레이어가 조작할 수 있는 Pawn class를 이용한 캐릭터로 움직일 수 있도록 한 코드입니다

# 주요 기능
* CharacterPawn.h / CharacterPawn.cpp: 캐릭터의 기본 동작 및 입력 처리를 담당하는 클래스입니다.
* PGGameMode.h / PGGameMode.cpp: 게임의 기본 모드를 정의하는 클래스입니다.
* PGPlayerController.h / PGPlayerController.cpp: 플레이어의 입력을 처리하는 컨트롤러 클래스입니다.

# CharacterPawn .h/.cpp
* 캐릭터의 기본 움직임과 입력 처리를 담당합니다.
* 물리 기반의 중력 및 충돌 감지를 구현합니다
<pre>
<code>
	void MoveForward(const struct FInputActionValue& Value); // Pawn 상하
	void MoveRight(const struct FInputActionValue& Value); // Pawn 좌우
	void Look(const struct FInputActionValue& Value); // Pawn 화면 전환
	void Roll(const struct FInputActionValue& Value); // Roll 방향 회전
	void MoveUpDown(const struct FInputActionValue& Value); // Pawn 상승 하강
</code>
</pre>

# APGGameMode
* 게임의 기본 모드를 설정합니다.
* 기본 캐릭터 및 플레이어 컨트롤러를 정의합니다.
<pre>
<code>
APGGameMode::APGGameMode()
{
    // 기본 설정 값 변경
    DefaultPawnClass = ACharacterPawn::StaticClass();
    PlayerControllerClass = APGPlayerController::StaticClass(); 
}
</code>
</pre>

# APGPlayerController
* 플레이어의 입력을 처리합니다.
* 입력 매핑을 설정하여 다양한 입력 방식을 지원합니다.
<pre>
<code>
  if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
  {

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
    {

        if (InputMappingContext)
        {

            Subsystem->AddMappingContext(InputMappingContext, 0); // 입력 맵핑 콘텍스트 추가

        }

    }

}
</code>
</pre>
