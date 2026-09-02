// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Bricks/Brick_Base.h"

#include "Components/BoxComponent.h"


// Sets default values
ABrick_Base::ABrick_Base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BrickMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BrickMesh"));
	
	SetRootComponent(BoxCollision);
	BrickMesh->SetupAttachment(BoxCollision);
}

// Called when the game starts or when spawned
void ABrick_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABrick_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABrick_Base::Bounced_Implementation()
{
	IBouncable::Bounced_Implementation();
	
}

void ABrick_Base::Destruct_Implementation()
{
	if (!IsValid(this))
		return;
	
	IDestructible::Destruct_Implementation();
	
	OnBrickDestruct.Broadcast(this);
}

