// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball/Ball_BB.h"

#include "Ball/Datas/BallDatas_BB.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ABall_BB::ABall_BB()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	
	ProjectileMovement->SetUpdatedComponent(SphereCollision);
	
	SetRootComponent(SphereCollision);
	StaticMesh->SetupAttachment(SphereCollision);
	
}

// Called when the game starts or when spawned
void ABall_BB::BeginPlay()
{
	Super::BeginPlay();
	
	if (bAutoInit)
	{
		Init();
	}
}

// Called every frame
void ABall_BB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABall_BB::Init()
{
	if (bHasInit)
		return;
	
	bHasInit = true;
	
	if (IsValid(Datas) && IsValid(ProjectileMovement))
	{
		FireInDirection(FVector::UpVector);
		
		ProjectileMovement->InitialSpeed = Datas->InitialSpeed;
		ProjectileMovement->MaxSpeed = Datas->MaxSpeed;
	}
}

void ABall_BB::Bounced_Implementation()
{
	IBouncable::Bounced_Implementation();
	
	if (!IsValid(this))
		return;
	
	OnBallBounced.Broadcast(this);
	
	ReceiveOnBounced();
}

void ABall_BB::Destruct_Implementation()
{
	IDestructible::Destruct_Implementation();
	
	if (!IsValid(this))
		return;
	
	OnBallDestruct.Broadcast(this);
	
	ReceiveOnDestruct();
	
	if (IsValid(this))
	{
		this->Destroy();
		return;
	}
}

void ABall_BB::FireInDirection(const FVector& InDirection)
{
	if (!IsValid(ProjectileMovement))
		return;
	
	ProjectileMovement->Velocity = InDirection * ProjectileMovement->InitialSpeed;
}

