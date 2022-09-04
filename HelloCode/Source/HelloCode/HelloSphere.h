// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" //���� ���� == ������ �� �ּ����� ��ɸ� �־�� ��� ����
#include "GameFramework/Actor.h" // ���Ͷ�� ��ü�� � �������� �˾ƾ����� ����� �����ϱ� ������ ���ش�.
#include "HelloSphere.generated.h" // �𸮾� ��ü �����ÿ� ������ ���� �ϴ� ��� �ݵ�� ��Ŭ��� ��� �������� �;��Ѵ�.

UCLASS() //�𸮾� �ڵ��� �����ϴ� ��
class HELLOCODE_API AHelloSphere : public AActor  //��� �ڵ� �ȿ� ���͸� �����ϰڴ�.
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
