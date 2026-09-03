// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Bricks/Brick_Base.h"

#include "Bricks/Datas/BrickDatas_Base.h"
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

int ABrick_Base::GetScoreOnBounced() const
{
	if (!IsValid(Datas))
		return 0;
	
	return Datas->ScoreOnBounced;
}

int ABrick_Base::GetScoreOnDestruct() const
{
	if (!IsValid(Datas))
		return 0;
	
	return Datas->ScoreOnDestruct;
}

void ABrick_Base::Bounced_Implementation()
{
	IBouncable::Bounced_Implementation();
	
	if (!IsValid(this))
		return;
	
	OnBrickBounced.Broadcast(this);
	
	ReceiveOnBounced();
}

void ABrick_Base::Destruct_Implementation()
{
	IDestructible::Destruct_Implementation();
	
	if (!IsValid(this))
		return;
	
	OnBrickDestruct.Broadcast(this);
	
	ReceiveOnDestruct();
	
	if (bDestroyImmediatlyOnDestruct && IsValid(this))
	{
		this->Destroy();
		return;
	}
}

