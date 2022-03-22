// Fill out your copyright notice in the Description page of Project Settings.


#include "ArkanoidPlayerController.h"

#include "ArkanoidGameModeBase.h"
#include "ArkanoidPlayerState.h"
#include "Ball.h"
#include "PlayerPaddle.h"
#include "Kismet/GameplayStatics.h"

void AArkanoidPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<AArkanoidGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	StartInitialState();
}

void AArkanoidPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis(TEXT("HorizontalInput"), this, &AArkanoidPlayerController::HandleHorizonalAxis);
	InputComponent->BindAction(TEXT("LaunchInput"),	EInputEvent::IE_Pressed ,this, &AArkanoidPlayerController::HandleLaunch);
	
}

void AArkanoidPlayerController::HandleHorizonalAxis(float HorizontalInput)
{
	if (APawn* MyPawn = GetPawn())
	{
		MyPawn->AddMovementInput(FVector::ForwardVector, HorizontalInput);
	}
}

void AArkanoidPlayerController::HandleLaunch()
{
	if (GameOver)
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(UGameplayStatics::GetCurrentLevelName(GetWorld(), true)));
	}
	else if (IsValid(HoldingBall))
	{
		HoldingBall->DetachFromActor(* new FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
		HoldingBall->Launch();
	}
}

void AArkanoidPlayerController::StartInitialState()
{
	if (APlayerPaddle* MyPawn = Cast<APlayerPaddle>(GetPawn()))
	{
		MyPawn->MovementSpeed = GameMode->GetRoundSpeed();
		if (ABall* MyBall = GetWorld()->SpawnActor<ABall>(BallClass))
		{
			Balls.Add(MyBall);
			HoldingBall = MyBall;
			HoldingBall->BallSpeed  = GameMode->GetRoundSpeed();
			HoldingBall->SetActorLocation(MyPawn->GetActorLocation() + BallSpawnOffstet);
			HoldingBall->AttachToActor(MyPawn, *new FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
			HoldingBall->OnBallDestroyed.AddDynamic(this, &AArkanoidPlayerController::HandleDestroyedBall);
		}
	}
}

void AArkanoidPlayerController::HandleDestroyedBall(ABall* Ball)
{
	Balls.Remove(Ball);
	if (Balls.Num() == 0)
	{
		if (AArkanoidPlayerState* ArkanoidPlayerState = Cast<AArkanoidPlayerState>(PlayerState))
		{
			ArkanoidPlayerState->LoseLife();
			if (ArkanoidPlayerState->Life > 0)
			{
				StartInitialState();
			}
			else
			{
				UnPossess();
				OnGameOver.Broadcast(ArkanoidPlayerState->GetScore());
				GameOver = true;
			}
		}
	}
}

void AArkanoidPlayerController::CreateAndLaunchBall()
{
	if (APawn* MyPawn = GetPawn())
	{
		if (ABall* MyBall = GetWorld()->SpawnActor<ABall>(BallClass))
		{
			Balls.Add(MyBall);
			MyBall->BallSpeed = GameMode->GetRoundSpeed();
			MyBall->SetActorLocation(MyPawn->GetActorLocation() + BallSpawnOffstet);
			MyBall->OnBallDestroyed.AddDynamic(this, &AArkanoidPlayerController::HandleDestroyedBall);
			MyBall->Launch();
		}
	}
}

void AArkanoidPlayerController::DestroyBalls()
{
	for (ABall* Ball : Balls)
	{
		Ball->Destroy();
	}
	Balls.Empty();
}
