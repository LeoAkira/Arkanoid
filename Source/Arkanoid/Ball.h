// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBallDestroyed,class ABall*, Ball);

UCLASS()
class ARKANOID_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	ABall();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Sphere;

	UPROPERTY(EditAnywhere)
	FVector LaunchDirection;

	UPROPERTY(EditAnywhere)
	float BallSpeed;

	UPROPERTY(BlueprintAssignable)
	FOnBallDestroyed OnBallDestroyed;
	
	UFUNCTION(BlueprintImplementableEvent)
	void BounceFeedback();

	UFUNCTION(BlueprintImplementableEvent)
	void DestroyFeedback();
	
private:
	FVector CurrentMovementDirection;
	bool Launched = false;
	bool DestroyedBrick = false;

public:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	void Launch();
	
	void Kill();

private:
	UFUNCTION()
	void OnBallCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};