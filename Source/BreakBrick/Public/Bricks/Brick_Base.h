// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bouncable/Bouncable.h"
#include "Destructible/Destructible.h"
#include "GameFramework/Actor.h"
#include "Brick_Base.generated.h"

class UBoxComponent;

UCLASS()
class BREAKBRICK_API ABrick_Base : public AActor, public IBouncable, public IDestructible
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABrick_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
public:
	
	// IBouncable
	virtual void Bounced_Implementation() override;
	
	// IDestructible
	virtual void Destruct_Implementation() override;
	
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBrickDestruct, ABrick_Base*, InBrick);
	FOnBrickDestruct OnBrickDestruct;
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> BoxCollision;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> BrickMesh;
	
	
};
