// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" //작은 느낌 == 빌드할 때 최소한의 기능만 넣어둔 헤더 파일
#include "GameFramework/Actor.h" // 액터라는 객체가 어떤 형태인지 알아야지만 상속이 가능하기 때문에 써준다.
#include "HelloSphere.generated.h" // 언리얼 객체 생성시에 무조건 들어가야 하는 헤더 반드시 인클루드 헤더 마지막에 와야한다.

UCLASS() //언리얼 코드라고 선언하는 것
class HELLOCODE_API AHelloSphere : public AActor  //헬로 코드 안에 액터를 생성하겠다.
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHelloSphere();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	class UTextRenderComponent* TextRenderComponent;
	
UFUNCTION()
	void MyOnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

UFUNCTION()	
	void MyOnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
