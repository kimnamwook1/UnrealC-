// Fill out your copyright notice in the Description page of Project Settings.


#include "BountyDashPowerUp.h"
#include "PowerUpObject.h"
#include "Obstacle.h"
#include "Components/SphereComponent.h"
#include "BountyDashCharacter.h"


ABountyDashPowerUp::ABountyDashPowerUp()
{
	PrimaryActorTick.bCanEverTick = true;

	PowerUp = CreateDefaultSubobject<UPowerUpObject>(TEXT("PowerUp"));
	check(PowerUp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	check(Mesh);

	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Mesh->SetCollisionProfileName("OverlapAllDynamic");

	FString AssetName;
	switch (PowerUp->GetType())
	{
	case EPowerUp::SPEED:
		AssetName = "StaticMesh'/Game/StarterContent/Shapes/Shape_QuadPyramid.Shape_QuadPyramid'";
		break;
	case EPowerUp::SMASH:
		AssetName = "StaticMesh'/Game/StarterContent/Shapes/Shape_WideCapsule.Shape_WideCapsule'";
		break;
	case EPowerUp::MAGNET:
		AssetName = "StaticMesh'/Game/StarterContent/Shapes/Shape_Pipe_180.Shape_Pipe_180'";
		break;
	default:
		break;
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> myMesh(&AssetName.GetCharArray()[0]);

	if (myMesh.Succeeded())
	{
		Mesh->SetStaticMesh(myMesh.Object);
	}
}

void ABountyDashPowerUp::MyOnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->GetClass()->IsChildOf(AObstacle::StaticClass()))
	{
		USphereComponent* otherSphere = Cast<USphereComponent>(OtherActor->GetComponentByClass(USphereComponent::StaticClass()));

		if (otherSphere)
		{
			FVector vec = GetActorLocation();
			float offsetZ = OtherActor->GetActorLocation().Z + (otherSphere->GetUnscaledSphereRadius()) + Collider->GetUnscaledSphereRadius();
			SetActorLocation(FVector(vec.X, vec.Y, offsetZ));
			
			//AddActorLocalOffset(FVector(0.0f, 0.0f, (otherSphere->GetUnscaledSphereRadius()) + Collider->GetUnscaledSphereRadius() * 2));
		}
	}

	if (OtherActor->GetClass()->IsChildOf(ABountyDashCharacter::StaticClass()))
	{
		ABountyDashCharacter* thisChar = Cast<ABountyDashCharacter>(OtherActor);
		if (thisChar)
		{
			thisChar->PowerUp(PowerUp->GetType());
			GetWorld()->DestroyActor(this);
		}
	}
}
