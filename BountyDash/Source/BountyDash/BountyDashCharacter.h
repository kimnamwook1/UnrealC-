// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BountyDash.h"
#include "PowerUpObject.h"
#include "GameFramework/Character.h"
#include "BountyDashCharacter.generated.h"


UCLASS()
class BOUNTYDASH_API ABountyDashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABountyDashCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // 키 입력시 사용하는 함수


public:
	UPROPERTY(EditAnywhere, Category = Logic)
	TArray<class ATargetPoint*> TargetArray; 

	UPROPERTY(EditAnywhere, Category = Logic)
	float CharSpeed;

	UPROPERTY(EditAnywhere, Category = Sound)
	UAudioComponent* hitObstacleSound;

	UPROPERTY(EditAnywhere, Category = Sound)
	UAudioComponent* digSound;

protected:
	//플레이어와 카메라 간의 거리를 유지하기 위한 카메라 붐
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;
	//타켓 뷰로 사용할 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;
	//플레이어 점수
	UPROPERTY(BlueprintReadOnly)
	int32 Score;
	
	UPROPERTY(EditAnywhere, Category = PowerUps)
	float SmashTime;

	UPROPERTY(EditAnywhere, Category = PowerUps)
	float MagnetTime;

	UPROPERTY(EditAnywhere, Category = PowerUps)
	float MagnetReach;
	
	//킬포인트
	float KillPoint;

private:
	//캐릭터가 서있는 위치 데이터
	short CurrentLocation;
	FVector DesiredLocation;
	bool bBeingPushed;
	bool CanSmash;
	bool CanMagnet;

public: 
	void ScoreUp();
	void PowerUp(EPowerUp Type);
	int GetScore();
	
protected:
	void MoveRight();
	void MoveLeft();
	void CoinMagnet(); 

	UFUNCTION()
	void MyOnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyInex, bool bFromSweep, const FHitResult&SweepResult);

	UFUNCTION()
	void MyOnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OverlappedCompent, int32 OtherBodyInex);

	UFUNCTION()
		void StopSmash();

	UFUNCTION()
		void StopMagnet();

	UFUNCTION()
	void Reset();
};
