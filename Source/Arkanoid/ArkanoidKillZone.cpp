// Fill out your copyright notice in the Description page of Project Settings.


#include "ArkanoidKillZone.h"

#include "Ball.h"
#include "BasePowerUp.h"
#include "Components/BoxComponent.h"

AArkanoidKillZone::AArkanoidKillZone()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
}

void AArkanoidKillZone::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentHit.AddDynamic(this, &AArkanoidKillZone::OnKillzoneHit);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AArkanoidKillZone::OnKillzoneOverlap);
}

void AArkanoidKillZone::OnKillzoneHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ABall* Ball = Cast<ABall>(OtherActor))
	{
		Ball->Kill();
	}
}

void AArkanoidKillZone::OnKillzoneOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ABasePowerUp>(OtherActor))
	{
		OtherActor->Destroy();
	}
}