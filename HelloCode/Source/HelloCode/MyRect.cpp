// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRect.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AMyRect::AMyRect() : MoveRect{ EMoveRect::Right }
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(Scene);

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Rock.SM_Rock'"));

	if (MeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
	}
}

// Called when the game starts or when spawned
void AMyRect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyRect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	switch (MoveRect)
	{
	case EMoveRect::Right:
		Mesh->AddRelativeLocation(FVector(10.0f, 0.0f, 0.0f));
		if (Mesh->GetRelativeLocation().X > 300)
		{
			MoveRect = EMoveRect::Up;
		}
		break;

	case EMoveRect::Up:
		Mesh->AddRelativeLocation(FVector(0.0f, 0.0f, 10.0f));
		if (Mesh->GetRelativeLocation().Z > 300)
		{
			MoveRect = EMoveRect::Left;
		}
		break;

	case EMoveRect::Left:
		Mesh->AddRelativeLocation(FVector(-10.0f, 0.0f, 0.0f));
		if (Mesh->GetRelativeLocation().X < 0)
		{
			MoveRect = EMoveRect::Down;
		}
		break;

	case EMoveRect::Down:
		Mesh->AddRelativeLocation(FVector(0.0f, 0.0f, -10.0f));
		if (Mesh->GetRelativeLocation().Z < 0)
		{
			MoveRect = EMoveRect::Right;
		}
		break;
	}

}

