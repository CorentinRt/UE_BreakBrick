// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Player_BB.h"

#include "Components/BoxComponent.h"


// Sets default values
APlayer_BB::APlayer_BB()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	
	SetRootComponent(BoxCollision);
	PlayerMesh->SetupAttachment(BoxCollision);
}

// Called when the game starts or when spawned
void APlayer_BB::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayer_BB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayer_BB::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

