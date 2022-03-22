// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

#include "BasePowerUp.h"
#include "Brick.h"
#include "PlayerPaddle.h"
#include "Kismet/KismetMathLibrary.h"

ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	RootComponent = Sphere;
}

void ABall::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABall::OnBallCollision);
	Sphere->OnComponentHit.AddDynamic(this, &ABall::OnBallHit);
	CurrentMovementDirection = FVector::ZeroVector;
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Launched)
	{
		AddActorLocalOffset(CurrentMovementDirection * BallSpeed * DeltaTime, true);
		DestroyedBrick = false;
	}
}

void ABall::Launch()
{
	CurrentMovementDirection = LaunchDirection.GetSafeNormal();
	Launched = true;
}

void ABall::Kill()
{
	OnBallDestroyed.Broadcast(this);
	DestroyFeedback();
	Destroy();
}

void ABall::OnBallCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	return;
	if (Cast<APlayerPaddle>(OtherActor))
	{
		FVector PaddleExtent = OtherActor->GetComponentsBoundingBox().GetExtent();
		float HitXPosition = (GetActorLocation().X - OtherActor->GetActorLocation().X) / PaddleExtent.X;
		if (HitXPosition < 0) HitXPosition = UKismetMathLibrary::FMin(HitXPosition, -0.2f);
		else HitXPosition = UKismetMathLibrary::FMax(HitXPosition, 0.2f);
		CurrentMovementDirection = FVector(HitXPosition,0,1).GetSafeNormal();
		BounceFeedback();
	}
	else if (!Cast<ABall>(OtherActor) && !Cast<ABasePowerUp>(OtherActor))
	{
		FVector ReflectionDirection = UKismetMathLibrary::GetReflectionVector(CurrentMovementDirection, SweepResult.ImpactNormal);
		CurrentMovementDirection = (ReflectionDirection * FVector(1,0,1)).GetSafeNormal();

		if (!DestroyedBrick)
		{
			if (ABrick* Brick = Cast<ABrick>(OtherActor))
			{
				Brick->DamageBrick();
				DestroyedBrick = true;
			}			
		}
		BounceFeedback();
	}
}

void ABall::OnBallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (Cast<APlayerPaddle>(OtherActor))
	{
		FVector PaddleExtent = OtherActor->GetComponentsBoundingBox().GetExtent();
		float HitXPosition = (GetActorLocation().X - OtherActor->GetActorLocation().X) / PaddleExtent.X;
		if (HitXPosition < 0) HitXPosition = UKismetMathLibrary::FMin(HitXPosition, -0.2f);
		else HitXPosition = UKismetMathLibrary::FMax(HitXPosition, 0.2f);
		CurrentMovementDirection = FVector(HitXPosition,0,1).GetSafeNormal();
		BounceFeedback();
	}
	else if (!Cast<ABall>(OtherActor) && !Cast<ABasePowerUp>(OtherActor))
	{
		FVector ReflectionDirection = UKismetMathLibrary::GetReflectionVector(CurrentMovementDirection, Hit.ImpactNormal);
		CurrentMovementDirection = (ReflectionDirection * FVector(1,0,1)).GetSafeNormal();

		if (!DestroyedBrick)
		{
			if (ABrick* Brick = Cast<ABrick>(OtherActor))
			{
				Brick->DamageBrick();
				DestroyedBrick = true;
			}			
		}
		BounceFeedback();
	}
}

