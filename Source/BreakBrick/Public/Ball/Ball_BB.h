// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bouncable/Bouncable.h"
#include "Destructible/Destructible.h"
#include "GameFramework/Actor.h"
#include "Ball_BB.generated.h"

class UBallDatas_BB;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class BREAKBRICK_API ABall_BB : public AActor, public IDestructible, public IBouncable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABall_BB();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	UFUNCTION(blueprintCallable)
	void Init();
	
private:
	
	UPROPERTY(EditAnywhere)
	bool bAutoInit = false;
	
	UPROPERTY(VisibleAnywhere)
	bool bHasInit = false;
	
	
	
#pragma region Components
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> SphereCollision;
	
	
#pragma endregion 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UBallDatas_BB> Datas;
	
	
	// IBouncable
	void Bounced_Implementation() override;
	
	// IDestructible
	void Destruct_Implementation() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnBounced();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnDestruct();
	
	
public:
	
	UFUNCTION(BlueprintCallable)
	void FireInDirection(const FVector& InDirection);
	
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBallDestruct, ABall_BB*, InBall);
	FOnBallDestruct OnBallDestruct;
	
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBallBounced, ABall_BB*, InBall);
	FOnBallBounced OnBallBounced;
	
};
