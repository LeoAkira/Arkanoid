// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePowerUp.h"

#include "PlayerPaddle.h"

ABasePowerUp::ABasePowerUp()
{
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
}

void ABasePowerUp::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &ABasePowerUp::OnOverlap);
}

void ABasePowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(0, -1, 0) * FallSpeed * DeltaTime, true);
}

void ABasePowerUp::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<APlayerPaddle>(OtherActor))
	{
		UsePowerUp();
		Destroy();
	}
}

