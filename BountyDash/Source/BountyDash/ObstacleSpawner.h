// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BountyDash.h"
#include "GameFramework/Actor.h"
#include "ObstacleSpawner.generated.h"

class AObstalce;

UCLASS()
class BOUNTYDASH_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	void SpawnObstacle();

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<TSubclassOf<class AObstacle>> ObstaclesToSpwan;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<class ATargetPoint*> SpawnTargets;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float SpawnTimer;

	UPROPERTY()
	USceneComponent* Scene;

private:
	float KillPoint;
	float SpawnPoint;
	float timeSinceLastSpawn;
};
