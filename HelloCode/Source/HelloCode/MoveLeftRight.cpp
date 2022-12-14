// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveLeftRight.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
AMoveLeftRight::AMoveLeftRight() : MoveRL{ EMoveRL::RL_Right }    //1) IsRight(true) //멤버변수는 여기에서 초기화 해줘도 된다.
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
void AMoveLeftRight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMoveLeftRight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	switch (MoveRL)
	{
	case EMoveRL::RL_Right:
		Mesh->AddRelativeLocation(FVector(10.0f, 0.0f, 0.0f));
		if (Mesh->GetRelativeLocation().X > 500)
		{
			MoveRL = EMoveRL::RL_Left;
		}
		break;

	case EMoveRL::RL_Left:
		Mesh->AddRelativeLocation(FVector(-10.0f, 0.0f, 0.0f));
		if (Mesh -> GetRelativeLocation().X < -500)
		{
			MoveRL = EMoveRL::RL_Right;
		}
		break;
	}

	/*
	float X = Mesh->GetRelativeLocation().X;

	if (IsRight == true)
	{
		
		Mesh->AddRelativeLocation(FVector(10.0f, 0.0f, 0.0f));
		if (X > 500)
		{
			IsRight = false;
		}
	}
	else
	{
		Mesh->AddRelativeLocation(FVector(-10.0f, 0.0f, 0.0f));
		if (X < -500)
		{
			IsRight = true;
		}
	}*/
}

